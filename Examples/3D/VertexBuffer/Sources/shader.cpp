/*
**  ClanLib SDK
**  Copyright (c) 1997-2012 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Mark Page
*/

#include "precomp.h"

#include "shader.h"
const char Shader::vertex_hlsl[] =
	"\n"
	"cbuffer ProgramUniforms\n"
	"{\n"
	"	float4x4 cl_ModelViewMatrix;\n"
	"	float4x4 cl_ModelViewProjectionMatrix;\n"
	"	float3x3 cl_NormalMatrix;\n"
	"	float4 padding;\n"
	"	float4 LightDiffuse;\n"
	"	float4 LightAmbient;\n"
	"	float3 LightVector;\n"
	"}\n"
	"struct VertexIn\n"
	"	{\n"
	"		float3 InPosition : InPosition;\n"
	"		float3 InNormal : InNormal;\n"
	"		float4 InMaterialAmbient : InMaterialAmbient;\n"
	"	};\n"
	"\n"
	"	struct VertexOut\n"
	"	{\n"
	"		float4 PositionInProjection : SV_Position;\n"
	"	};\n"
	"\n"
	"	VertexOut main(VertexIn input)\n"
	"	{\n"
	"		VertexOut output;\n"
	"		float4 in_position = float4(input.InPosition.xyz, 1.0);\n"
	"		output.PositionInProjection = mul(cl_ModelViewProjectionMatrix,in_position);\n"
	"		return output;\n"
	"	}\n";

const char Shader::fragment_hlsl[] =
	"\n"
	"cbuffer ProgramUniforms\n"
	"{\n"
	"	float4x4 cl_ModelViewMatrix;\n"
	"	float4x4 cl_ModelViewProjectionMatrix;\n"
	"	float3x3 cl_NormalMatrix;\n"
	"	float4 padding;\n"
	"	float4 LightDiffuse;\n"
	"	float4 LightAmbient;\n"
	"	float3 LightVector;\n"
	"}\n"
	"\n"
	"struct PixelIn\n"
	"{\n"
	"	float4 ScreenPos : SV_Position;\n"
	"};\n"
	"\n"
	"struct PixelOut\n"
	"{\n"
	"	float4 cl_FragColor : SV_Target0;\n"
	"};\n"
	"\n"
	"PixelOut main(PixelIn input)\n"
	"{\n"
	"	PixelOut output;\n"
	"	output.cl_FragColor = float4(1,1,1,1);\n"
	"	return output;\n"
	"}\n";

const char Shader::vertex_glsl[] =
	"\n"
	"#version 150\n"
	"\n"
	"in vec3 InPosition;"
	"in vec3 InNormal;"
	"in vec4 InMaterialAmbient;"
	"layout (std140) uniform ProgramUniforms\n"
	"{\n"
	"	mat4 cl_ModelViewMatrix;\n"
	"	mat4 cl_ModelViewProjectionMatrix;\n"
	"	mat3 cl_NormalMatrix;\n"
	"	vec4 padding;\n"
	"	vec4 LightDiffuse;\n"
	"	vec4 LightAmbient;\n"
	"	vec3 LightVector;\n"
	"};\n"
	"out vec3 WorldSpaceNormal; \n"
	"out vec3 WorldSpacePosition; \n"
	"out vec4 ObjPos;\n"
	"flat out vec4 MaterialAmbient;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	vec4 in_position = vec4(InPosition.xyz, 1.0);\n"
	"	gl_Position = cl_ModelViewProjectionMatrix * in_position;\n"
	"	WorldSpaceNormal = normalize( cl_NormalMatrix * InNormal);\n"
	"	WorldSpacePosition = InPosition;\n"
	"   MaterialAmbient = InMaterialAmbient;\n"
	"	ObjPos = cl_ModelViewMatrix * in_position;\n"
	"}\n"
	;

const char Shader::fragment_glsl[] =
	"\n"
	"#version 150\n"
	"\n"
	"in vec3 WorldSpaceNormal; \n"
	"in vec3 WorldSpacePosition; \n"
	"in vec4 ObjPos;\n"
	"flat in vec4 MaterialAmbient;\n"
	"out vec4 cl_FragColor;\n"
	"layout (std140) uniform ProgramUniforms\n"
	"{\n"
	"	mat4 cl_ModelViewMatrix;\n"
	"	mat4 cl_ModelViewProjectionMatrix;\n"
	"	mat3 cl_NormalMatrix;\n"
	"	vec4 padding;\n"
	"	vec4 LightDiffuse;\n"
	"	vec4 LightAmbient;\n"
	"	vec3 LightVector;\n"
	"};\n"
	"\n"
	"void main()\n"
	"{\n"
	"	vec3 eye = -normalize(ObjPos.xyz); \n"
	"	vec4 diff = vec4(0); \n"
	"\n"
	"	vec3 world_space_normal = normalize(WorldSpaceNormal);\n"
	"	float nDotL = max(0.0, dot(world_space_normal, LightVector)); \n"
	"	diff += LightDiffuse * nDotL;\n"
	"	vec4 final_texture_color = vec4(MaterialAmbient.rgb,1.0);\n"
	"	cl_FragColor = LightAmbient * final_texture_color + diff * final_texture_color;\n"
	"	cl_FragColor.a = MaterialAmbient.a;\n"
	"}\n"
	;

Shader::Shader(GraphicContext &gc)
{
	ShaderLanguage shader_language = gc.get_shader_language();
	ShaderObject vertex_shader(gc, shadertype_vertex, shader_language==shader_glsl ? vertex_glsl : vertex_hlsl);
	if(!vertex_shader.compile())
	{
		std::string log = vertex_shader.get_info_log();
		throw Exception(string_format("Unable to compile vertex shader object: %1", log));
	}

	ShaderObject fragment_shader(gc, shadertype_fragment, shader_language==shader_glsl ? fragment_glsl : fragment_hlsl);
	if(!fragment_shader.compile())
	{
		std::string log = fragment_shader.get_info_log();
		throw Exception(string_format("Unable to compile fragment shader object: %1", log));
	}

	program_object = ProgramObject(gc);
	program_object.attach(vertex_shader);
	program_object.attach(fragment_shader);
	program_object.bind_attribute_location(0, "InPosition");
	program_object.bind_attribute_location(1, "InNormal");
	program_object.bind_attribute_location(2, "InMaterialAmbient");
	program_object.bind_frag_data_location(0, "cl_FragColor");
	if (!program_object.link())
	{
		throw Exception(string_format("Unable to link program object: %1", program_object.get_info_log()));
	}

	program_object.set_uniform_buffer_index("ProgramUniforms", 0);

	gpu_uniforms = clan::UniformVector<ProgramUniforms>(gc, 1);

	uniforms.LightAmbient = Vec4f(0.2f, 0.2f, 0.2f, 1.0f);
	uniforms.LightVector = Vec3f(0.0f, 0.0f, -1.0f);
	uniforms.LightDiffuse = Vec4f(0.7f, 0.7f, 0.7f, 1.0f);

}

void Shader::Use(GraphicContext &gc, const Mat4f &matrix_modelview, const Mat4f &matrix_modelview_projection, const Mat4f &matrix_normal)
{
	uniforms.cl_ModelViewProjectionMatrix = matrix_modelview_projection;
	uniforms.cl_ModelViewMatrix = matrix_modelview;
	uniforms.cl_NormalMatrix = matrix_normal;
	gpu_uniforms.upload_data(gc, &uniforms, 1);
	gc.set_uniform_buffer(0, gpu_uniforms);

	gc.set_program_object(program_object);
}
