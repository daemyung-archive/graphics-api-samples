// MIT License
//
// Copyright (c) 2018 DAEMYUNG, JANG
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef GL_SAMPLE_H
#define GL_SAMPLE_H

#include <windows.h>
#include <gl/gl.h>
#include <khronos/gl/wglext.h>
#include <khronos/gl/glext.h>

#include "common/sample.h"

using PFN_glDrawRangeElements = PFNGLDRAWRANGEELEMENTSPROC;
using PFN_glTexImage3D        = PFNGLTEXIMAGE3DPROC;
using PFN_glTexSubImage3D     = PFNGLTEXSUBIMAGE3DPROC;
using PFN_glCopyTexSubImage3D = PFNGLCOPYTEXSUBIMAGE3DPROC;

#define APPLY_MACRO_TO_GL_API_1_2(macro) \
    macro(glDrawRangeElements)           \
    macro(glTexImage3D)                  \
    macro(glTexSubImage3D)               \
    macro(glCopyTexSubImage3D)

using PFN_glActiveTexture           = PFNGLACTIVETEXTUREPROC;
using PFN_glSampleCoverage          = PFNGLSAMPLECOVERAGEPROC;
using PFN_glCompressedTexImage3D    = PFNGLCOMPRESSEDTEXIMAGE3DPROC;
using PFN_glCompressedTexImage2D    = PFNGLCOMPRESSEDTEXIMAGE2DPROC;
using PFN_glCompressedTexImage1D    = PFNGLCOMPRESSEDTEXIMAGE1DPROC;
using PFN_glCompressedTexSubImage3D = PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC;
using PFN_glCompressedTexSubImage2D = PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC;
using PFN_glCompressedTexSubImage1D = PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC;
using PFN_glGetCompressedTexImage   = PFNGLGETCOMPRESSEDTEXIMAGEPROC;
using PFN_glClientActiveTexture     = PFNGLCLIENTACTIVETEXTUREPROC;
using PFN_glMultiTexCoord1d         = PFNGLMULTITEXCOORD1DPROC;
using PFN_glMultiTexCoord1dv        = PFNGLMULTITEXCOORD1DVPROC;
using PFN_glMultiTexCoord1f         = PFNGLMULTITEXCOORD1FPROC;
using PFN_glMultiTexCoord1fv        = PFNGLMULTITEXCOORD1FVPROC;
using PFN_glMultiTexCoord1i         = PFNGLMULTITEXCOORD1IPROC;
using PFN_glMultiTexCoord1iv        = PFNGLMULTITEXCOORD1IVPROC;
using PFN_glMultiTexCoord1s         = PFNGLMULTITEXCOORD1SPROC;
using PFN_glMultiTexCoord1sv        = PFNGLMULTITEXCOORD1SVPROC;
using PFN_glMultiTexCoord2d         = PFNGLMULTITEXCOORD2DPROC;
using PFN_glMultiTexCoord2dv        = PFNGLMULTITEXCOORD2DVPROC;
using PFN_glMultiTexCoord2f         = PFNGLMULTITEXCOORD2FPROC;
using PFN_glMultiTexCoord2fv        = PFNGLMULTITEXCOORD2FVPROC;
using PFN_glMultiTexCoord2i         = PFNGLMULTITEXCOORD2IPROC;
using PFN_glMultiTexCoord2iv        = PFNGLMULTITEXCOORD2IVPROC;
using PFN_glMultiTexCoord2s         = PFNGLMULTITEXCOORD2SPROC;
using PFN_glMultiTexCoord2sv        = PFNGLMULTITEXCOORD2SVPROC;
using PFN_glMultiTexCoord3d         = PFNGLMULTITEXCOORD3DPROC;
using PFN_glMultiTexCoord3dv        = PFNGLMULTITEXCOORD3DVPROC;
using PFN_glMultiTexCoord3f         = PFNGLMULTITEXCOORD3FPROC;
using PFN_glMultiTexCoord3fv        = PFNGLMULTITEXCOORD3FVPROC;
using PFN_glMultiTexCoord3i         = PFNGLMULTITEXCOORD3IPROC;
using PFN_glMultiTexCoord3iv        = PFNGLMULTITEXCOORD3IVPROC;
using PFN_glMultiTexCoord3s         = PFNGLMULTITEXCOORD3SPROC;
using PFN_glMultiTexCoord3sv        = PFNGLMULTITEXCOORD3SVPROC;
using PFN_glMultiTexCoord4d         = PFNGLMULTITEXCOORD4DPROC;
using PFN_glMultiTexCoord4dv        = PFNGLMULTITEXCOORD4DVPROC;
using PFN_glMultiTexCoord4f         = PFNGLMULTITEXCOORD4FPROC;
using PFN_glMultiTexCoord4fv        = PFNGLMULTITEXCOORD4FVPROC;
using PFN_glMultiTexCoord4i         = PFNGLMULTITEXCOORD4IPROC;
using PFN_glMultiTexCoord4iv        = PFNGLMULTITEXCOORD4IVPROC;
using PFN_glMultiTexCoord4s         = PFNGLMULTITEXCOORD4SPROC;
using PFN_glMultiTexCoord4sv        = PFNGLMULTITEXCOORD4SVPROC;
using PFN_glLoadTransposeMatrixf    = PFNGLLOADTRANSPOSEMATRIXFPROC;
using PFN_glLoadTransposeMatrixd    = PFNGLLOADTRANSPOSEMATRIXDPROC;
using PFN_glMultTransposeMatrixf    = PFNGLMULTTRANSPOSEMATRIXFPROC;
using PFN_glMultTransposeMatrixd    = PFNGLMULTTRANSPOSEMATRIXDPROC;

#define APPLY_MACRO_TO_GL_API_1_3(macro) \
    macro(glActiveTexture)               \
    macro(glSampleCoverage)              \
    macro(glCompressedTexImage3D)        \
    macro(glCompressedTexImage2D)        \
    macro(glCompressedTexImage1D)        \
    macro(glCompressedTexSubImage3D)     \
    macro(glCompressedTexSubImage2D)     \
    macro(glCompressedTexSubImage1D)     \
    macro(glGetCompressedTexImage)       \
    macro(glClientActiveTexture)         \
    macro(glMultiTexCoord1d)             \
    macro(glMultiTexCoord1dv)            \
    macro(glMultiTexCoord1f)             \
    macro(glMultiTexCoord1fv)            \
    macro(glMultiTexCoord1i)             \
    macro(glMultiTexCoord1iv)            \
    macro(glMultiTexCoord1s)             \
    macro(glMultiTexCoord1sv)            \
    macro(glMultiTexCoord2d)             \
    macro(glMultiTexCoord2dv)            \
    macro(glMultiTexCoord2f)             \
    macro(glMultiTexCoord2fv)            \
    macro(glMultiTexCoord2i)             \
    macro(glMultiTexCoord2iv)            \
    macro(glMultiTexCoord2s)             \
    macro(glMultiTexCoord2sv)            \
    macro(glMultiTexCoord3d)             \
    macro(glMultiTexCoord3dv)            \
    macro(glMultiTexCoord3f)             \
    macro(glMultiTexCoord3fv)            \
    macro(glMultiTexCoord3i)             \
    macro(glMultiTexCoord3iv)            \
    macro(glMultiTexCoord3s)             \
    macro(glMultiTexCoord3sv)            \
    macro(glMultiTexCoord4d)             \
    macro(glMultiTexCoord4dv)            \
    macro(glMultiTexCoord4f)             \
    macro(glMultiTexCoord4fv)            \
    macro(glMultiTexCoord4i)             \
    macro(glMultiTexCoord4iv)            \
    macro(glMultiTexCoord4s)             \
    macro(glMultiTexCoord4sv)            \
    macro(glLoadTransposeMatrixf)        \
    macro(glLoadTransposeMatrixd)        \
    macro(glMultTransposeMatrixf)        \
    macro(glMultTransposeMatrixd)

using PFN_glBlendFuncSeparate     = PFNGLBLENDFUNCSEPARATEPROC;
using PFN_glMultiDrawArrays       = PFNGLMULTIDRAWARRAYSPROC;
using PFN_glMultiDrawElements     = PFNGLMULTIDRAWELEMENTSPROC;
using PFN_glPointParameterf       = PFNGLPOINTPARAMETERFPROC;
using PFN_glPointParameterfv      = PFNGLPOINTPARAMETERFVPROC;
using PFN_glPointParameteri       = PFNGLPOINTPARAMETERIPROC;
using PFN_glPointParameteriv      = PFNGLPOINTPARAMETERIVPROC;
using PFN_glFogCoordf             = PFNGLFOGCOORDFPROC;
using PFN_glFogCoordfv            = PFNGLFOGCOORDFVPROC;
using PFN_glFogCoordd             = PFNGLFOGCOORDDPROC;
using PFN_glFogCoorddv            = PFNGLFOGCOORDDVPROC;
using PFN_glFogCoordPointer       = PFNGLFOGCOORDPOINTERPROC;
using PFN_glSecondaryColor3b      = PFNGLSECONDARYCOLOR3BPROC;
using PFN_glSecondaryColor3bv     = PFNGLSECONDARYCOLOR3BVPROC;
using PFN_glSecondaryColor3d      = PFNGLSECONDARYCOLOR3DPROC;
using PFN_glSecondaryColor3dv     = PFNGLSECONDARYCOLOR3DVPROC;
using PFN_glSecondaryColor3f      = PFNGLSECONDARYCOLOR3FPROC;
using PFN_glSecondaryColor3fv     = PFNGLSECONDARYCOLOR3FVPROC;
using PFN_glSecondaryColor3i      = PFNGLSECONDARYCOLOR3IPROC;
using PFN_glSecondaryColor3iv     = PFNGLSECONDARYCOLOR3IVPROC;
using PFN_glSecondaryColor3s      = PFNGLSECONDARYCOLOR3SPROC;
using PFN_glSecondaryColor3sv     = PFNGLSECONDARYCOLOR3SVPROC;
using PFN_glSecondaryColor3ub     = PFNGLSECONDARYCOLOR3UBPROC;
using PFN_glSecondaryColor3ubv    = PFNGLSECONDARYCOLOR3UBVPROC;
using PFN_glSecondaryColor3ui     = PFNGLSECONDARYCOLOR3UIPROC;
using PFN_glSecondaryColor3uiv    = PFNGLSECONDARYCOLOR3UIVPROC;
using PFN_glSecondaryColor3us     = PFNGLSECONDARYCOLOR3USPROC;
using PFN_glSecondaryColor3usv    = PFNGLSECONDARYCOLOR3USVPROC;
using PFN_glSecondaryColorPointer = PFNGLSECONDARYCOLORPOINTERPROC;
using PFN_glWindowPos2d           = PFNGLWINDOWPOS2DPROC;
using PFN_glWindowPos2dv          = PFNGLWINDOWPOS2DVPROC;
using PFN_glWindowPos2f           = PFNGLWINDOWPOS2FPROC;
using PFN_glWindowPos2fv          = PFNGLWINDOWPOS2FVPROC;
using PFN_glWindowPos2i           = PFNGLWINDOWPOS2IPROC;
using PFN_glWindowPos2iv          = PFNGLWINDOWPOS2IVPROC;
using PFN_glWindowPos2s           = PFNGLWINDOWPOS2SPROC;
using PFN_glWindowPos2sv          = PFNGLWINDOWPOS2SVPROC;
using PFN_glWindowPos3d           = PFNGLWINDOWPOS3DPROC;
using PFN_glWindowPos3dv          = PFNGLWINDOWPOS3DVPROC;
using PFN_glWindowPos3f           = PFNGLWINDOWPOS3FPROC;
using PFN_glWindowPos3fv          = PFNGLWINDOWPOS3FVPROC;
using PFN_glWindowPos3i           = PFNGLWINDOWPOS3IPROC;
using PFN_glWindowPos3iv          = PFNGLWINDOWPOS3IVPROC;
using PFN_glWindowPos3s           = PFNGLWINDOWPOS3SPROC;
using PFN_glWindowPos3sv          = PFNGLWINDOWPOS3SVPROC;
using PFN_glBlendColor            = PFNGLBLENDCOLORPROC;
using PFN_glBlendEquation         = PFNGLBLENDEQUATIONPROC;

#define APPLY_MACRO_TO_GL_API_1_4(macro) \
    macro(glBlendFuncSeparate)           \
    macro(glMultiDrawArrays)             \
    macro(glMultiDrawElements)           \
    macro(glPointParameterf)             \
    macro(glPointParameterfv)            \
    macro(glPointParameteri)             \
    macro(glPointParameteriv)            \
    macro(glFogCoordf)                   \
    macro(glFogCoordfv)                  \
    macro(glFogCoordd)                   \
    macro(glFogCoorddv)                  \
    macro(glFogCoordPointer)             \
    macro(glSecondaryColor3b)            \
    macro(glSecondaryColor3bv)           \
    macro(glSecondaryColor3d)            \
    macro(glSecondaryColor3dv)           \
    macro(glSecondaryColor3f)            \
    macro(glSecondaryColor3fv)           \
    macro(glSecondaryColor3i)            \
    macro(glSecondaryColor3iv)           \
    macro(glSecondaryColor3s)            \
    macro(glSecondaryColor3sv)           \
    macro(glSecondaryColor3ub)           \
    macro(glSecondaryColor3ubv)          \
    macro(glSecondaryColor3ui)           \
    macro(glSecondaryColor3uiv)          \
    macro(glSecondaryColor3us)           \
    macro(glSecondaryColor3usv)          \
    macro(glSecondaryColorPointer)       \
    macro(glWindowPos2d)                 \
    macro(glWindowPos2dv)                \
    macro(glWindowPos2f)                 \
    macro(glWindowPos2fv)                \
    macro(glWindowPos2i)                 \
    macro(glWindowPos2iv)                \
    macro(glWindowPos2s)                 \
    macro(glWindowPos2sv)                \
    macro(glWindowPos3d)                 \
    macro(glWindowPos3dv)                \
    macro(glWindowPos3f)                 \
    macro(glWindowPos3fv)                \
    macro(glWindowPos3i)                 \
    macro(glWindowPos3iv)                \
    macro(glWindowPos3s)                 \
    macro(glWindowPos3sv)                \
    macro(glBlendColor)                  \
    macro(glBlendEquation)

using PFN_glGenQueries           = PFNGLGENQUERIESPROC;
using PFN_glDeleteQueries        = PFNGLDELETEQUERIESPROC;
using PFN_glIsQuery              = PFNGLISQUERYPROC;
using PFN_glBeginQuery           = PFNGLBEGINQUERYPROC;
using PFN_glEndQuery             = PFNGLENDQUERYPROC;
using PFN_glGetQueryiv           = PFNGLGETQUERYIVPROC;
using PFN_glGetQueryObjectiv     = PFNGLGETQUERYOBJECTIVPROC;
using PFN_glGetQueryObjectuiv    = PFNGLGETQUERYOBJECTUIVPROC;
using PFN_glBindBuffer           = PFNGLBINDBUFFERPROC;
using PFN_glDeleteBuffers        = PFNGLDELETEBUFFERSPROC;
using PFN_glGenBuffers           = PFNGLGENBUFFERSPROC;
using PFN_glIsBuffer             = PFNGLISBUFFERPROC;
using PFN_glBufferData           = PFNGLBUFFERDATAPROC;
using PFN_glBufferSubData        = PFNGLBUFFERSUBDATAPROC;
using PFN_glGetBufferSubData     = PFNGLGETBUFFERSUBDATAPROC;
using PFN_glMapBuffer            = PFNGLMAPBUFFERPROC;
using PFN_glUnmapBuffer          = PFNGLUNMAPBUFFERPROC;
using PFN_glGetBufferParameteriv = PFNGLGETBUFFERPARAMETERIVPROC;
using PFN_glGetBufferPointerv    = PFNGLGETBUFFERPOINTERVPROC;

#define APPLY_MACRO_TO_GL_API_1_5(macro) \
    macro(glGenQueries)                  \
    macro(glDeleteQueries)               \
    macro(glIsQuery)                     \
    macro(glBeginQuery)                  \
    macro(glEndQuery)                    \
    macro(glGetQueryiv)                  \
    macro(glGetQueryObjectiv)            \
    macro(glGetQueryObjectuiv)           \
    macro(glBindBuffer)                  \
    macro(glDeleteBuffers)               \
    macro(glGenBuffers)                  \
    macro(glIsBuffer)                    \
    macro(glBufferData)                  \
    macro(glBufferSubData)               \
    macro(glGetBufferSubData)            \
    macro(glMapBuffer)                   \
    macro(glUnmapBuffer)                 \
    macro(glGetBufferParameteriv)        \
    macro(glGetBufferPointerv)

using PFN_glBlendEquationSeparate    = PFNGLBLENDEQUATIONSEPARATEPROC;
using PFN_glDrawBuffers              = PFNGLDRAWBUFFERSPROC;
using PFN_glStencilOpSeparate        = PFNGLSTENCILOPSEPARATEPROC;
using PFN_glStencilFuncSeparate      = PFNGLSTENCILFUNCSEPARATEPROC;
using PFN_glStencilMaskSeparate      = PFNGLSTENCILMASKSEPARATEPROC;
using PFN_glAttachShader             = PFNGLATTACHSHADERPROC;
using PFN_glBindAttribLocation       = PFNGLBINDATTRIBLOCATIONPROC;
using PFN_glCompileShader            = PFNGLCOMPILESHADERPROC;
using PFN_glCreateProgram            = PFNGLCREATEPROGRAMPROC;
using PFN_glCreateShader             = PFNGLCREATESHADERPROC;
using PFN_glDeleteProgram            = PFNGLDELETEPROGRAMPROC;
using PFN_glDeleteShader             = PFNGLDELETESHADERPROC;
using PFN_glDetachShader             = PFNGLDETACHSHADERPROC;
using PFN_glDisableVertexAttribArray = PFNGLDISABLEVERTEXATTRIBARRAYPROC;
using PFN_glEnableVertexAttribArray  = PFNGLENABLEVERTEXATTRIBARRAYPROC;
using PFN_glGetActiveAttrib          = PFNGLGETACTIVEATTRIBPROC;
using PFN_glGetActiveUniform         = PFNGLGETACTIVEUNIFORMPROC;
using PFN_glGetAttachedShaders       = PFNGLGETATTACHEDSHADERSPROC;
using PFN_glGetAttribLocation        = PFNGLGETATTRIBLOCATIONPROC;
using PFN_glGetProgramiv             = PFNGLGETPROGRAMIVPROC;
using PFN_glGetProgramInfoLog        = PFNGLGETPROGRAMINFOLOGPROC;
using PFN_glGetShaderiv              = PFNGLGETSHADERIVPROC;
using PFN_glGetShaderInfoLog         = PFNGLGETSHADERINFOLOGPROC;
using PFN_glGetShaderSource          = PFNGLGETSHADERSOURCEPROC;
using PFN_glGetUniformLocation       = PFNGLGETUNIFORMLOCATIONPROC;
using PFN_glGetUniformfv             = PFNGLGETUNIFORMFVPROC;
using PFN_glGetUniformiv             = PFNGLGETUNIFORMIVPROC;
using PFN_glGetVertexAttribdv        = PFNGLGETVERTEXATTRIBDVPROC;
using PFN_glGetVertexAttribfv        = PFNGLGETVERTEXATTRIBFVPROC;
using PFN_glGetVertexAttribiv        = PFNGLGETVERTEXATTRIBIVPROC;
using PFN_glGetVertexAttribPointerv  = PFNGLGETVERTEXATTRIBPOINTERVPROC;
using PFN_glIsProgram                = PFNGLISPROGRAMPROC;
using PFN_glIsShader                 = PFNGLISSHADERPROC;
using PFN_glLinkProgram              = PFNGLLINKPROGRAMPROC;
using PFN_glShaderSource             = PFNGLSHADERSOURCEPROC;
using PFN_glUseProgram               = PFNGLUSEPROGRAMPROC;
using PFN_glUniform1f                = PFNGLUNIFORM1FPROC;
using PFN_glUniform2f                = PFNGLUNIFORM2FPROC;
using PFN_glUniform3f                = PFNGLUNIFORM3FPROC;
using PFN_glUniform4f                = PFNGLUNIFORM4FPROC;
using PFN_glUniform1i                = PFNGLUNIFORM1IPROC;
using PFN_glUniform2i                = PFNGLUNIFORM2IPROC;
using PFN_glUniform3i                = PFNGLUNIFORM3IPROC;
using PFN_glUniform4i                = PFNGLUNIFORM4IPROC;
using PFN_glUniform1fv               = PFNGLUNIFORM1FVPROC;
using PFN_glUniform2fv               = PFNGLUNIFORM2FVPROC;
using PFN_glUniform3fv               = PFNGLUNIFORM3FVPROC;
using PFN_glUniform4fv               = PFNGLUNIFORM4FVPROC;
using PFN_glUniform1iv               = PFNGLUNIFORM1IVPROC;
using PFN_glUniform2iv               = PFNGLUNIFORM2IVPROC;
using PFN_glUniform3iv               = PFNGLUNIFORM3IVPROC;
using PFN_glUniform4iv               = PFNGLUNIFORM4IVPROC;
using PFN_glUniformMatrix2fv         = PFNGLUNIFORMMATRIX2FVPROC;
using PFN_glUniformMatrix3fv         = PFNGLUNIFORMMATRIX3FVPROC;
using PFN_glUniformMatrix4fv         = PFNGLUNIFORMMATRIX4FVPROC;
using PFN_glValidateProgram          = PFNGLVALIDATEPROGRAMPROC;
using PFN_glVertexAttrib1d           = PFNGLVERTEXATTRIB1DPROC;
using PFN_glVertexAttrib1dv          = PFNGLVERTEXATTRIB1DVPROC;
using PFN_glVertexAttrib1f           = PFNGLVERTEXATTRIB1FPROC;
using PFN_glVertexAttrib1fv          = PFNGLVERTEXATTRIB1FVPROC;
using PFN_glVertexAttrib1s           = PFNGLVERTEXATTRIB1SPROC;
using PFN_glVertexAttrib1sv          = PFNGLVERTEXATTRIB1SVPROC;
using PFN_glVertexAttrib2d           = PFNGLVERTEXATTRIB2DPROC;
using PFN_glVertexAttrib2dv          = PFNGLVERTEXATTRIB2DVPROC;
using PFN_glVertexAttrib2f           = PFNGLVERTEXATTRIB2FPROC;
using PFN_glVertexAttrib2fv          = PFNGLVERTEXATTRIB2FVPROC;
using PFN_glVertexAttrib2s           = PFNGLVERTEXATTRIB2SPROC;
using PFN_glVertexAttrib2sv          = PFNGLVERTEXATTRIB2SVPROC;
using PFN_glVertexAttrib3d           = PFNGLVERTEXATTRIB3DPROC;
using PFN_glVertexAttrib3dv          = PFNGLVERTEXATTRIB3DVPROC;
using PFN_glVertexAttrib3f           = PFNGLVERTEXATTRIB3FPROC;
using PFN_glVertexAttrib3fv          = PFNGLVERTEXATTRIB3FVPROC;
using PFN_glVertexAttrib3s           = PFNGLVERTEXATTRIB3SPROC;
using PFN_glVertexAttrib3sv          = PFNGLVERTEXATTRIB3SVPROC;
using PFN_glVertexAttrib4Nbv         = PFNGLVERTEXATTRIB4NBVPROC;
using PFN_glVertexAttrib4Niv         = PFNGLVERTEXATTRIB4NIVPROC;
using PFN_glVertexAttrib4Nsv         = PFNGLVERTEXATTRIB4NSVPROC;
using PFN_glVertexAttrib4Nub         = PFNGLVERTEXATTRIB4NUBPROC;
using PFN_glVertexAttrib4Nubv        = PFNGLVERTEXATTRIB4NUBVPROC;
using PFN_glVertexAttrib4Nuiv        = PFNGLVERTEXATTRIB4NUIVPROC;
using PFN_glVertexAttrib4Nusv        = PFNGLVERTEXATTRIB4NUSVPROC;
using PFN_glVertexAttrib4bv          = PFNGLVERTEXATTRIB4BVPROC;
using PFN_glVertexAttrib4d           = PFNGLVERTEXATTRIB4DPROC;
using PFN_glVertexAttrib4dv          = PFNGLVERTEXATTRIB4DVPROC;
using PFN_glVertexAttrib4f           = PFNGLVERTEXATTRIB4FPROC;
using PFN_glVertexAttrib4fv          = PFNGLVERTEXATTRIB4FVPROC;
using PFN_glVertexAttrib4iv          = PFNGLVERTEXATTRIB4IVPROC;
using PFN_glVertexAttrib4s           = PFNGLVERTEXATTRIB4SPROC;
using PFN_glVertexAttrib4sv          = PFNGLVERTEXATTRIB4SVPROC;
using PFN_glVertexAttrib4ubv         = PFNGLVERTEXATTRIB4UBVPROC;
using PFN_glVertexAttrib4uiv         = PFNGLVERTEXATTRIB4UIVPROC;
using PFN_glVertexAttrib4usv         = PFNGLVERTEXATTRIB4USVPROC;
using PFN_glVertexAttribPointer      = PFNGLVERTEXATTRIBPOINTERPROC;

#define APPLY_MACRO_TO_GL_API_2_0(macro) \
    macro(glBlendEquationSeparate)       \
    macro(glDrawBuffers)                 \
    macro(glStencilOpSeparate)           \
    macro(glStencilFuncSeparate)         \
    macro(glStencilMaskSeparate)         \
    macro(glAttachShader)                \
    macro(glBindAttribLocation)          \
    macro(glCompileShader)               \
    macro(glCreateProgram)               \
    macro(glCreateShader)                \
    macro(glDeleteProgram)               \
    macro(glDetachShader)                \
    macro(glDeleteShader)                \
    macro(glDisableVertexAttribArray)    \
    macro(glEnableVertexAttribArray)     \
    macro(glGetActiveAttrib)             \
    macro(glGetActiveUniform)            \
    macro(glGetAttachedShaders)          \
    macro(glGetAttribLocation)           \
    macro(glGetProgramiv)                \
    macro(glGetProgramInfoLog)           \
    macro(glGetShaderiv)                 \
    macro(glGetShaderInfoLog)            \
    macro(glGetShaderSource)             \
    macro(glGetUniformLocation)          \
    macro(glGetUniformfv)                \
    macro(glGetUniformiv)                \
    macro(glGetVertexAttribdv)           \
    macro(glGetVertexAttribfv)           \
    macro(glGetVertexAttribiv)           \
    macro(glGetVertexAttribPointerv)     \
    macro(glIsProgram)                   \
    macro(glIsShader)                    \
    macro(glLinkProgram)                 \
    macro(glShaderSource)                \
    macro(glUseProgram)                  \
    macro(glUniform1f)                   \
    macro(glUniform2f)                   \
    macro(glUniform3f)                   \
    macro(glUniform4f)                   \
    macro(glUniform1i)                   \
    macro(glUniform2i)                   \
    macro(glUniform3i)                   \
    macro(glUniform4i)                   \
    macro(glUniform1fv)                  \
    macro(glUniform2fv)                  \
    macro(glUniform3fv)                  \
    macro(glUniform4fv)                  \
    macro(glUniform1iv)                  \
    macro(glUniform2iv)                  \
    macro(glUniform3iv)                  \
    macro(glUniform4iv)                  \
    macro(glUniformMatrix2fv)            \
    macro(glUniformMatrix3fv)            \
    macro(glUniformMatrix4fv)            \
    macro(glValidateProgram)             \
    macro(glVertexAttrib1d)              \
    macro(glVertexAttrib1dv)             \
    macro(glVertexAttrib1f)              \
    macro(glVertexAttrib1fv)             \
    macro(glVertexAttrib1s)              \
    macro(glVertexAttrib1sv)             \
    macro(glVertexAttrib2d)              \
    macro(glVertexAttrib2dv)             \
    macro(glVertexAttrib2f)              \
    macro(glVertexAttrib2fv)             \
    macro(glVertexAttrib2s)              \
    macro(glVertexAttrib2sv)             \
    macro(glVertexAttrib3d)              \
    macro(glVertexAttrib3dv)             \
    macro(glVertexAttrib3f)              \
    macro(glVertexAttrib3fv)             \
    macro(glVertexAttrib3s)              \
    macro(glVertexAttrib3sv)             \
    macro(glVertexAttrib4Nbv)            \
    macro(glVertexAttrib4Niv)            \
    macro(glVertexAttrib4Nsv)            \
    macro(glVertexAttrib4Nub)            \
    macro(glVertexAttrib4Nubv)           \
    macro(glVertexAttrib4Nuiv)           \
    macro(glVertexAttrib4Nusv)           \
    macro(glVertexAttrib4bv)             \
    macro(glVertexAttrib4d)              \
    macro(glVertexAttrib4dv)             \
    macro(glVertexAttrib4f)              \
    macro(glVertexAttrib4fv)             \
    macro(glVertexAttrib4iv)             \
    macro(glVertexAttrib4s)              \
    macro(glVertexAttrib4sv)             \
    macro(glVertexAttrib4ubv)            \
    macro(glVertexAttrib4uiv)            \
    macro(glVertexAttrib4usv)            \
    macro(glVertexAttribPointer)

using PFN_glUniformMatrix2x3fv = PFNGLUNIFORMMATRIX2X3FVPROC;
using PFN_glUniformMatrix3x2fv = PFNGLUNIFORMMATRIX3X2FVPROC;
using PFN_glUniformMatrix2x4fv = PFNGLUNIFORMMATRIX2X4FVPROC;
using PFN_glUniformMatrix4x2fv = PFNGLUNIFORMMATRIX4X2FVPROC;
using PFN_glUniformMatrix3x4fv = PFNGLUNIFORMMATRIX3X4FVPROC;
using PFN_glUniformMatrix4x3fv = PFNGLUNIFORMMATRIX4X3FVPROC;

#define APPLY_MACRO_TO_GL_API_2_1(macro) \
    macro(glUniformMatrix2x3fv)          \
    macro(glUniformMatrix3x2fv)          \
    macro(glUniformMatrix2x4fv)          \
    macro(glUniformMatrix4x2fv)          \
    macro(glUniformMatrix3x4fv)          \
    macro(glUniformMatrix4x3fv)

using PFN_glColorMaski                          = PFNGLCOLORMASKIPROC;
using PFN_glGetBooleani_v                       = PFNGLGETBOOLEANI_VPROC;
using PFN_glGetIntegeri_v                       = PFNGLGETINTEGERI_VPROC;
using PFN_glEnablei                             = PFNGLENABLEIPROC;
using PFN_glDisablei                            = PFNGLDISABLEIPROC;
using PFN_glIsEnabledi                          = PFNGLISENABLEDIPROC;
using PFN_glBeginTransformFeedback              = PFNGLBEGINTRANSFORMFEEDBACKPROC;
using PFN_glEndTransformFeedback                = PFNGLENDTRANSFORMFEEDBACKPROC;
using PFN_glBindBufferRange                     = PFNGLBINDBUFFERRANGEPROC;
using PFN_glBindBufferBase                      = PFNGLBINDBUFFERBASEPROC;
using PFN_glTransformFeedbackVaryings           = PFNGLTRANSFORMFEEDBACKVARYINGSPROC;
using PFN_glGetTransformFeedbackVarying         = PFNGLGETTRANSFORMFEEDBACKVARYINGPROC;
using PFN_glClampColor                          = PFNGLCLAMPCOLORPROC;
using PFN_glBeginConditionalRender              = PFNGLBEGINCONDITIONALRENDERPROC;
using PFN_glEndConditionalRender                = PFNGLENDCONDITIONALRENDERPROC;
using PFN_glVertexAttribIPointer                = PFNGLVERTEXATTRIBIPOINTERPROC;
using PFN_glGetVertexAttribIiv                  = PFNGLGETVERTEXATTRIBIIVPROC;
using PFN_glGetVertexAttribIuiv                 = PFNGLGETVERTEXATTRIBIUIVPROC;
using PFN_glVertexAttribI1i                     = PFNGLVERTEXATTRIBI1IPROC;
using PFN_glVertexAttribI2i                     = PFNGLVERTEXATTRIBI2IPROC;
using PFN_glVertexAttribI3i                     = PFNGLVERTEXATTRIBI3IPROC;
using PFN_glVertexAttribI4i                     = PFNGLVERTEXATTRIBI4IPROC;
using PFN_glVertexAttribI1ui                    = PFNGLVERTEXATTRIBI1UIPROC;
using PFN_glVertexAttribI2ui                    = PFNGLVERTEXATTRIBI2UIPROC;
using PFN_glVertexAttribI3ui                    = PFNGLVERTEXATTRIBI3UIPROC;
using PFN_glVertexAttribI4ui                    = PFNGLVERTEXATTRIBI4UIPROC;
using PFN_glVertexAttribI1iv                    = PFNGLVERTEXATTRIBI1IVPROC;
using PFN_glVertexAttribI2iv                    = PFNGLVERTEXATTRIBI2IVPROC;
using PFN_glVertexAttribI3iv                    = PFNGLVERTEXATTRIBI3IVPROC;
using PFN_glVertexAttribI4iv                    = PFNGLVERTEXATTRIBI4IVPROC;
using PFN_glVertexAttribI1uiv                   = PFNGLVERTEXATTRIBI1UIVPROC;
using PFN_glVertexAttribI2uiv                   = PFNGLVERTEXATTRIBI2UIVPROC;
using PFN_glVertexAttribI3uiv                   = PFNGLVERTEXATTRIBI3UIVPROC;
using PFN_glVertexAttribI4uiv                   = PFNGLVERTEXATTRIBI4UIVPROC;
using PFN_glVertexAttribI4bv                    = PFNGLVERTEXATTRIBI4BVPROC;
using PFN_glVertexAttribI4sv                    = PFNGLVERTEXATTRIBI4SVPROC;
using PFN_glVertexAttribI4ubv                   = PFNGLVERTEXATTRIBI4UBVPROC;
using PFN_glVertexAttribI4usv                   = PFNGLVERTEXATTRIBI4USVPROC;
using PFN_glGetUniformuiv                       = PFNGLGETUNIFORMUIVPROC;
using PFN_glBindFragDataLocation                = PFNGLBINDFRAGDATALOCATIONPROC;
using PFN_glGetFragDataLocation                 = PFNGLGETFRAGDATALOCATIONPROC;
using PFN_glUniform1ui                          = PFNGLUNIFORM1UIPROC;
using PFN_glUniform2ui                          = PFNGLUNIFORM2UIPROC;
using PFN_glUniform3ui                          = PFNGLUNIFORM3UIPROC;
using PFN_glUniform4ui                          = PFNGLUNIFORM4UIPROC;
using PFN_glUniform1uiv                         = PFNGLUNIFORM1UIVPROC;
using PFN_glUniform2uiv                         = PFNGLUNIFORM2UIVPROC;
using PFN_glUniform3uiv                         = PFNGLUNIFORM3UIVPROC;
using PFN_glUniform4uiv                         = PFNGLUNIFORM4UIVPROC;
using PFN_glTexParameterIiv                     = PFNGLTEXPARAMETERIIVPROC;
using PFN_glTexParameterIuiv                    = PFNGLTEXPARAMETERIUIVPROC;
using PFN_glGetTexParameterIiv                  = PFNGLGETTEXPARAMETERIIVPROC;
using PFN_glGetTexParameterIuiv                 = PFNGLGETTEXPARAMETERIUIVPROC;
using PFN_glClearBufferiv                       = PFNGLCLEARBUFFERIVPROC;
using PFN_glClearBufferuiv                      = PFNGLCLEARBUFFERUIVPROC;
using PFN_glClearBufferfv                       = PFNGLCLEARBUFFERFVPROC;
using PFN_glClearBufferfi                       = PFNGLCLEARBUFFERFIPROC;
using PFN_glGetStringi                          = PFNGLGETSTRINGIPROC;
using PFN_glIsRenderbuffer                      = PFNGLISRENDERBUFFERPROC;
using PFN_glBindRenderbuffer                    = PFNGLBINDRENDERBUFFERPROC;
using PFN_glDeleteRenderbuffers                 = PFNGLDELETERENDERBUFFERSPROC;
using PFN_glGenRenderbuffers                    = PFNGLGENRENDERBUFFERSPROC;
using PFN_glRenderbufferStorage                 = PFNGLRENDERBUFFERSTORAGEPROC;
using PFN_glGetRenderbufferParameteriv          = PFNGLGETRENDERBUFFERPARAMETERIVPROC;
using PFN_glIsFramebuffer                       = PFNGLISFRAMEBUFFERPROC;
using PFN_glBindFramebuffer                     = PFNGLBINDFRAMEBUFFERPROC;
using PFN_glDeleteFramebuffers                  = PFNGLDELETEFRAMEBUFFERSPROC;
using PFN_glGenFramebuffers                     = PFNGLGENFRAMEBUFFERSPROC;
using PFN_glCheckFramebufferStatus              = PFNGLCHECKFRAMEBUFFERSTATUSPROC;
using PFN_glFramebufferTexture1D                = PFNGLFRAMEBUFFERTEXTURE1DPROC;
using PFN_glFramebufferTexture2D                = PFNGLFRAMEBUFFERTEXTURE2DPROC;
using PFN_glFramebufferTexture3D                = PFNGLFRAMEBUFFERTEXTURE3DPROC;
using PFN_glFramebufferRenderbuffer             = PFNGLFRAMEBUFFERRENDERBUFFERPROC;
using PFN_glGetFramebufferAttachmentParameteriv = PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC;
using PFN_glGenerateMipmap                      = PFNGLGENERATEMIPMAPPROC;
using PFN_glBlitFramebuffer                     = PFNGLBLITFRAMEBUFFERPROC;
using PFN_glRenderbufferStorageMultisample      = PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC;
using PFN_glFramebufferTextureLayer             = PFNGLFRAMEBUFFERTEXTURELAYERPROC;
using PFN_glMapBufferRange                      = PFNGLMAPBUFFERRANGEPROC;
using PFN_glFlushMappedBufferRange              = PFNGLFLUSHMAPPEDBUFFERRANGEPROC;
using PFN_glBindVertexArray                     = PFNGLBINDVERTEXARRAYPROC;
using PFN_glDeleteVertexArrays                  = PFNGLDELETEVERTEXARRAYSPROC;
using PFN_glGenVertexArrays                     = PFNGLGENVERTEXARRAYSPROC;
using PFN_glIsVertexArray                       = PFNGLISVERTEXARRAYPROC;

#define APPLY_MACRO_TO_GL_API_3_0(macro)         \
    macro(glColorMaski)                          \
    macro(glGetBooleani_v)                       \
    macro(glGetIntegeri_v)                       \
    macro(glEnablei)                             \
    macro(glDisablei)                            \
    macro(glIsEnabledi)                          \
    macro(glBeginTransformFeedback)              \
    macro(glEndTransformFeedback)                \
    macro(glBindBufferRange)                     \
    macro(glBindBufferBase)                      \
    macro(glTransformFeedbackVaryings)           \
    macro(glGetTransformFeedbackVarying)         \
    macro(glClampColor)                          \
    macro(glBeginConditionalRender)              \
    macro(glEndConditionalRender)                \
    macro(glVertexAttribIPointer)                \
    macro(glGetVertexAttribIiv)                  \
    macro(glGetVertexAttribIuiv)                 \
    macro(glVertexAttribI1i)                     \
    macro(glVertexAttribI2i)                     \
    macro(glVertexAttribI3i)                     \
    macro(glVertexAttribI4i)                     \
    macro(glVertexAttribI1ui)                    \
    macro(glVertexAttribI2ui)                    \
    macro(glVertexAttribI3ui)                    \
    macro(glVertexAttribI4ui)                    \
    macro(glVertexAttribI1iv)                    \
    macro(glVertexAttribI2iv)                    \
    macro(glVertexAttribI3iv)                    \
    macro(glVertexAttribI4iv)                    \
    macro(glVertexAttribI1uiv)                   \
    macro(glVertexAttribI2uiv)                   \
    macro(glVertexAttribI3uiv)                   \
    macro(glVertexAttribI4uiv)                   \
    macro(glVertexAttribI4bv)                    \
    macro(glVertexAttribI4sv)                    \
    macro(glVertexAttribI4ubv)                   \
    macro(glVertexAttribI4usv)                   \
    macro(glGetUniformuiv)                       \
    macro(glBindFragDataLocation)                \
    macro(glGetFragDataLocation)                 \
    macro(glUniform1ui)                          \
    macro(glUniform2ui)                          \
    macro(glUniform3ui)                          \
    macro(glUniform4ui)                          \
    macro(glUniform1uiv)                         \
    macro(glUniform2uiv)                         \
    macro(glUniform3uiv)                         \
    macro(glUniform4uiv)                         \
    macro(glTexParameterIiv)                     \
    macro(glTexParameterIuiv)                    \
    macro(glGetTexParameterIiv)                  \
    macro(glGetTexParameterIuiv)                 \
    macro(glClearBufferiv)                       \
    macro(glClearBufferuiv)                      \
    macro(glClearBufferfv)                       \
    macro(glClearBufferfi)                       \
    macro(glGetStringi)                          \
    macro(glIsRenderbuffer)                      \
    macro(glBindRenderbuffer)                    \
    macro(glDeleteRenderbuffers)                 \
    macro(glGenRenderbuffers)                    \
    macro(glRenderbufferStorage)                 \
    macro(glGetRenderbufferParameteriv)          \
    macro(glIsFramebuffer)                       \
    macro(glBindFramebuffer)                     \
    macro(glDeleteFramebuffers)                  \
    macro(glGenFramebuffers)                     \
    macro(glCheckFramebufferStatus)              \
    macro(glFramebufferTexture1D)                \
    macro(glFramebufferTexture2D)                \
    macro(glFramebufferTexture3D)                \
    macro(glFramebufferRenderbuffer)             \
    macro(glGetFramebufferAttachmentParameteriv) \
    macro(glGenerateMipmap)                      \
    macro(glBlitFramebuffer)                     \
    macro(glRenderbufferStorageMultisample)      \
    macro(glFramebufferTextureLayer)             \
    macro(glMapBufferRange)                      \
    macro(glFlushMappedBufferRange)              \
    macro(glBindVertexArray)                     \
    macro(glDeleteVertexArrays)                  \
    macro(glGenVertexArrays)                     \
    macro(glIsVertexArray)

using PFN_glDrawArraysInstanced       = PFNGLDRAWARRAYSINSTANCEDPROC;
using PFN_glDrawElementsInstanced     = PFNGLDRAWELEMENTSINSTANCEDPROC;
using PFN_glTexBuffer                 = PFNGLTEXBUFFERPROC;
using PFN_glPrimitiveRestartIndex     = PFNGLPRIMITIVERESTARTINDEXPROC;
using PFN_glCopyBufferSubData         = PFNGLCOPYBUFFERSUBDATAPROC;
using PFN_glGetUniformIndices         = PFNGLGETUNIFORMINDICESPROC;
using PFN_glGetActiveUniformsiv       = PFNGLGETACTIVEUNIFORMSIVPROC;
using PFN_glGetActiveUniformName      = PFNGLGETACTIVEUNIFORMNAMEPROC;
using PFN_glGetUniformBlockIndex      = PFNGLGETUNIFORMBLOCKINDEXPROC;
using PFN_glGetActiveUniformBlockiv   = PFNGLGETACTIVEUNIFORMBLOCKIVPROC;
using PFN_glGetActiveUniformBlockName = PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC;
using PFN_glUniformBlockBinding       = PFNGLUNIFORMBLOCKBINDINGPROC;

#define APPLY_MACRO_TO_GL_API_3_1(macro) \
    macro(glDrawArraysInstanced)         \
    macro(glDrawElementsInstanced)       \
    macro(glTexBuffer)                   \
    macro(glPrimitiveRestartIndex)       \
    macro(glCopyBufferSubData)           \
    macro(glGetUniformIndices)           \
    macro(glGetActiveUniformsiv)         \
    macro(glGetActiveUniformName)        \
    macro(glGetUniformBlockIndex)        \
    macro(glGetActiveUniformBlockiv)     \
    macro(glGetActiveUniformBlockName)   \
    macro(glUniformBlockBinding)

using PFN_glDrawElementsBaseVertex          = PFNGLDRAWELEMENTSBASEVERTEXPROC;
using PFN_glDrawRangeElementsBaseVertex     = PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC;
using PFN_glDrawElementsInstancedBaseVertex = PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC;
using PFN_glMultiDrawElementsBaseVertex     = PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC;
using PFN_glProvokingVertex                 = PFNGLPROVOKINGVERTEXPROC;
using PFN_glFenceSync                       = PFNGLFENCESYNCPROC;
using PFN_glIsSync                          = PFNGLISSYNCPROC;
using PFN_glDeleteSync                      = PFNGLDELETESYNCPROC;
using PFN_glClientWaitSync                  = PFNGLCLIENTWAITSYNCPROC;
using PFN_glWaitSync                        = PFNGLWAITSYNCPROC;
using PFN_glGetInteger64v                   = PFNGLGETINTEGER64VPROC;
using PFN_glGetSynciv                       = PFNGLGETSYNCIVPROC;
using PFN_glGetInteger64i_v                 = PFNGLGETINTEGER64I_VPROC;
using PFN_glGetBufferParameteri64v          = PFNGLGETBUFFERPARAMETERI64VPROC;
using PFN_glFramebufferTexture              = PFNGLFRAMEBUFFERTEXTUREPROC;
using PFN_glTexImage2DMultisample           = PFNGLTEXIMAGE2DMULTISAMPLEPROC;
using PFN_glTexImage3DMultisample           = PFNGLTEXIMAGE3DMULTISAMPLEPROC;
using PFN_glGetMultisamplefv                = PFNGLGETMULTISAMPLEFVPROC;
using PFN_glSampleMaski                     = PFNGLSAMPLEMASKIPROC;

#define APPLY_MACRO_TO_GL_API_3_2(macro)     \
    macro(glDrawElementsBaseVertex)          \
    macro(glDrawRangeElementsBaseVertex)     \
    macro(glDrawElementsInstancedBaseVertex) \
    macro(glMultiDrawElementsBaseVertex)     \
    macro(glProvokingVertex)                 \
    macro(glFenceSync)                       \
    macro(glIsSync)                          \
    macro(glDeleteSync)                      \
    macro(glClientWaitSync)                  \
    macro(glWaitSync)                        \
    macro(glGetInteger64v)                   \
    macro(glGetSynciv)                       \
    macro(glGetInteger64i_v)                 \
    macro(glGetBufferParameteri64v)          \
    macro(glFramebufferTexture)              \
    macro(glTexImage2DMultisample)           \
    macro(glTexImage3DMultisample)           \
    macro(glGetMultisamplefv)                \
    macro(glSampleMaski)

using PFN_glBindFragDataLocationIndexed = PFNGLBINDFRAGDATALOCATIONINDEXEDPROC;;
using PFN_glGetFragDataIndex            = PFNGLGETFRAGDATAINDEXPROC;
using PFN_glGenSamplers                 = PFNGLGENSAMPLERSPROC;
using PFN_glDeleteSamplers              = PFNGLDELETESAMPLERSPROC;
using PFN_glIsSampler                   = PFNGLISSAMPLERPROC;
using PFN_glBindSampler                 = PFNGLBINDSAMPLERPROC;
using PFN_glSamplerParameteri           = PFNGLSAMPLERPARAMETERIPROC;
using PFN_glSamplerParameteriv          = PFNGLSAMPLERPARAMETERIVPROC;
using PFN_glSamplerParameterf           = PFNGLSAMPLERPARAMETERFPROC;
using PFN_glSamplerParameterfv          = PFNGLSAMPLERPARAMETERFVPROC;
using PFN_glSamplerParameterIiv         = PFNGLSAMPLERPARAMETERIIVPROC;
using PFN_glSamplerParameterIuiv        = PFNGLSAMPLERPARAMETERIUIVPROC;
using PFN_glGetSamplerParameteriv       = PFNGLGETSAMPLERPARAMETERIVPROC;
using PFN_glGetSamplerParameterIiv      = PFNGLGETSAMPLERPARAMETERIIVPROC;
using PFN_glGetSamplerParameterfv       = PFNGLGETSAMPLERPARAMETERFVPROC;
using PFN_glGetSamplerParameterIuiv     = PFNGLGETSAMPLERPARAMETERIUIVPROC;
using PFN_glQueryCounter                = PFNGLQUERYCOUNTERPROC;
using PFN_glGetQueryObjecti64v          = PFNGLGETQUERYOBJECTI64VPROC;
using PFN_glGetQueryObjectui64v         = PFNGLGETQUERYOBJECTUI64VPROC;
using PFN_glVertexAttribDivisor         = PFNGLVERTEXATTRIBDIVISORPROC;
using PFN_glVertexAttribP1ui            = PFNGLVERTEXATTRIBP1UIPROC;
using PFN_glVertexAttribP1uiv           = PFNGLVERTEXATTRIBP1UIVPROC;
using PFN_glVertexAttribP2ui            = PFNGLVERTEXATTRIBP2UIPROC;
using PFN_glVertexAttribP2uiv           = PFNGLVERTEXATTRIBP2UIVPROC;
using PFN_glVertexAttribP3ui            = PFNGLVERTEXATTRIBP3UIPROC;
using PFN_glVertexAttribP3uiv           = PFNGLVERTEXATTRIBP3UIVPROC;
using PFN_glVertexAttribP4ui            = PFNGLVERTEXATTRIBP4UIPROC;
using PFN_glVertexAttribP4uiv           = PFNGLVERTEXATTRIBP4UIVPROC;
using PFN_glVertexP2ui                  = PFNGLVERTEXP2UIPROC;
using PFN_glVertexP2uiv                 = PFNGLVERTEXP2UIVPROC;
using PFN_glVertexP3ui                  = PFNGLVERTEXP3UIPROC;
using PFN_glVertexP3uiv                 = PFNGLVERTEXP3UIVPROC;
using PFN_glVertexP4ui                  = PFNGLVERTEXP4UIPROC;
using PFN_glVertexP4uiv                 = PFNGLVERTEXP4UIVPROC;
using PFN_glTexCoordP1ui                = PFNGLTEXCOORDP1UIPROC;
using PFN_glTexCoordP1uiv               = PFNGLTEXCOORDP1UIVPROC;
using PFN_glTexCoordP2ui                = PFNGLTEXCOORDP2UIPROC;
using PFN_glTexCoordP2uiv               = PFNGLTEXCOORDP2UIVPROC;
using PFN_glTexCoordP3ui                = PFNGLTEXCOORDP3UIPROC;
using PFN_glTexCoordP3uiv               = PFNGLTEXCOORDP3UIVPROC;
using PFN_glTexCoordP4ui                = PFNGLTEXCOORDP4UIPROC;
using PFN_glTexCoordP4uiv               = PFNGLTEXCOORDP4UIVPROC;
using PFN_glMultiTexCoordP1ui           = PFNGLMULTITEXCOORDP1UIPROC;
using PFN_glMultiTexCoordP1uiv          = PFNGLMULTITEXCOORDP1UIVPROC;
using PFN_glMultiTexCoordP2ui           = PFNGLMULTITEXCOORDP2UIPROC;
using PFN_glMultiTexCoordP2uiv          = PFNGLMULTITEXCOORDP2UIVPROC;
using PFN_glMultiTexCoordP3ui           = PFNGLMULTITEXCOORDP3UIPROC;
using PFN_glMultiTexCoordP3uiv          = PFNGLMULTITEXCOORDP3UIVPROC;
using PFN_glMultiTexCoordP4ui           = PFNGLMULTITEXCOORDP4UIPROC;
using PFN_glMultiTexCoordP4uiv          = PFNGLMULTITEXCOORDP4UIVPROC;
using PFN_glNormalP3ui                  = PFNGLNORMALP3UIPROC;
using PFN_glNormalP3uiv                 = PFNGLNORMALP3UIVPROC;
using PFN_glColorP3ui                   = PFNGLCOLORP3UIPROC;
using PFN_glColorP3uiv                  = PFNGLCOLORP3UIVPROC;
using PFN_glColorP4ui                   = PFNGLCOLORP4UIPROC;
using PFN_glColorP4uiv                  = PFNGLCOLORP4UIVPROC;
using PFN_glSecondaryColorP3ui          = PFNGLSECONDARYCOLORP3UIPROC;
using PFN_glSecondaryColorP3uiv         = PFNGLSECONDARYCOLORP3UIVPROC;

#define APPLY_MACRO_TO_GL_API_3_3(macro) \
    macro(glBindFragDataLocationIndexed) \
    macro(glGetFragDataIndex)            \
    macro(glGenSamplers)                 \
    macro(glDeleteSamplers)              \
    macro(glIsSampler)                   \
    macro(glBindSampler)                 \
    macro(glSamplerParameteri)           \
    macro(glSamplerParameteriv)          \
    macro(glSamplerParameterf)           \
    macro(glSamplerParameterfv)          \
    macro(glSamplerParameterIiv)         \
    macro(glSamplerParameterIuiv)        \
    macro(glGetSamplerParameteriv)       \
    macro(glGetSamplerParameterIiv)      \
    macro(glGetSamplerParameterfv)       \
    macro(glGetSamplerParameterIuiv)     \
    macro(glQueryCounter)                \
    macro(glGetQueryObjecti64v)          \
    macro(glGetQueryObjectui64v)         \
    macro(glVertexAttribDivisor)         \
    macro(glVertexAttribP1ui)            \
    macro(glVertexAttribP1uiv)           \
    macro(glVertexAttribP2ui)            \
    macro(glVertexAttribP2uiv)           \
    macro(glVertexAttribP3ui)            \
    macro(glVertexAttribP3uiv)           \
    macro(glVertexAttribP4ui)            \
    macro(glVertexAttribP4uiv)           \
    macro(glVertexP2ui)                  \
    macro(glVertexP2uiv)                 \
    macro(glVertexP3ui)                  \
    macro(glVertexP3uiv)                 \
    macro(glVertexP4ui)                  \
    macro(glVertexP4uiv)                 \
    macro(glTexCoordP1ui)                \
    macro(glTexCoordP1uiv)               \
    macro(glTexCoordP2ui)                \
    macro(glTexCoordP2uiv)               \
    macro(glTexCoordP3ui)                \
    macro(glTexCoordP3uiv)               \
    macro(glTexCoordP4ui)                \
    macro(glTexCoordP4uiv)               \
    macro(glMultiTexCoordP1ui)           \
    macro(glMultiTexCoordP1uiv)          \
    macro(glMultiTexCoordP2ui)           \
    macro(glMultiTexCoordP2uiv)          \
    macro(glMultiTexCoordP3ui)           \
    macro(glMultiTexCoordP3uiv)          \
    macro(glMultiTexCoordP4ui)           \
    macro(glMultiTexCoordP4uiv)          \
    macro(glNormalP3ui)                  \
    macro(glNormalP3uiv)                 \
    macro(glColorP3ui)                   \
    macro(glColorP3uiv)                  \
    macro(glColorP4ui)                   \
    macro(glColorP4uiv)                  \
    macro(glSecondaryColorP3ui)          \
    macro(glSecondaryColorP3uiv)

using PFN_glMinSampleShading               = PFNGLMINSAMPLESHADINGPROC;
using PFN_glBlendEquationi                 = PFNGLBLENDEQUATIONIPROC;
using PFN_glBlendEquationSeparatei         = PFNGLBLENDEQUATIONSEPARATEIPROC;
using PFN_glBlendFunci                     = PFNGLBLENDFUNCIPROC;
using PFN_glBlendFuncSeparatei             = PFNGLBLENDFUNCSEPARATEIPROC;
using PFN_glDrawArraysIndirect             = PFNGLDRAWARRAYSINDIRECTPROC;
using PFN_glDrawElementsIndirect           = PFNGLDRAWELEMENTSINDIRECTPROC;
using PFN_glUniform1d                      = PFNGLUNIFORM1DPROC;
using PFN_glUniform2d                      = PFNGLUNIFORM2DPROC;
using PFN_glUniform3d                      = PFNGLUNIFORM3DPROC;
using PFN_glUniform4d                      = PFNGLUNIFORM4DPROC;
using PFN_glUniform1dv                     = PFNGLUNIFORM1DVPROC;
using PFN_glUniform2dv                     = PFNGLUNIFORM2DVPROC;
using PFN_glUniform3dv                     = PFNGLUNIFORM3DVPROC;
using PFN_glUniform4dv                     = PFNGLUNIFORM4DVPROC;
using PFN_glUniformMatrix2dv               = PFNGLUNIFORMMATRIX2DVPROC;
using PFN_glUniformMatrix3dv               = PFNGLUNIFORMMATRIX3DVPROC;
using PFN_glUniformMatrix4dv               = PFNGLUNIFORMMATRIX4DVPROC;
using PFN_glUniformMatrix2x3dv             = PFNGLUNIFORMMATRIX2X3DVPROC;
using PFN_glUniformMatrix2x4dv             = PFNGLUNIFORMMATRIX2X4DVPROC;
using PFN_glUniformMatrix3x2dv             = PFNGLUNIFORMMATRIX3X2DVPROC;
using PFN_glUniformMatrix3x4dv             = PFNGLUNIFORMMATRIX3X4DVPROC;
using PFN_glUniformMatrix4x2dv             = PFNGLUNIFORMMATRIX4X2DVPROC;
using PFN_glUniformMatrix4x3dv             = PFNGLUNIFORMMATRIX4X3DVPROC;
using PFN_glGetUniformdv                   = PFNGLGETUNIFORMDVPROC;
using PFN_glGetSubroutineUniformLocation   = PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC;
using PFN_glGetSubroutineIndex             = PFNGLGETSUBROUTINEINDEXPROC;
using PFN_glGetActiveSubroutineUniformiv   = PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC;
using PFN_glGetActiveSubroutineUniformName = PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC;
using PFN_glGetActiveSubroutineName        = PFNGLGETACTIVESUBROUTINENAMEPROC;
using PFN_glUniformSubroutinesuiv          = PFNGLUNIFORMSUBROUTINESUIVPROC;
using PFN_glGetUniformSubroutineuiv        = PFNGLGETUNIFORMSUBROUTINEUIVPROC;
using PFN_glGetProgramStageiv              = PFNGLGETPROGRAMSTAGEIVPROC;
using PFN_glPatchParameteri                = PFNGLPATCHPARAMETERIPROC;
using PFN_glPatchParameterfv               = PFNGLPATCHPARAMETERFVPROC;
using PFN_glBindTransformFeedback          = PFNGLBINDTRANSFORMFEEDBACKPROC;
using PFN_glDeleteTransformFeedbacks       = PFNGLDELETETRANSFORMFEEDBACKSPROC;
using PFN_glGenTransformFeedbacks          = PFNGLGENTRANSFORMFEEDBACKSPROC;
using PFN_glIsTransformFeedback            = PFNGLISTRANSFORMFEEDBACKPROC;
using PFN_glPauseTransformFeedback         = PFNGLPAUSETRANSFORMFEEDBACKPROC;
using PFN_glResumeTransformFeedback        = PFNGLRESUMETRANSFORMFEEDBACKPROC;
using PFN_glDrawTransformFeedback          = PFNGLDRAWTRANSFORMFEEDBACKPROC;
using PFN_glDrawTransformFeedbackStream    = PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC;
using PFN_glBeginQueryIndexed              = PFNGLBEGINQUERYINDEXEDPROC;
using PFN_glEndQueryIndexed                = PFNGLENDQUERYINDEXEDPROC;
using PFN_glGetQueryIndexediv              = PFNGLGETQUERYINDEXEDIVPROC;

#define APPLY_MACRO_TO_GL_API_4_0(macro)    \
    macro(glMinSampleShading)               \
    macro(glBlendEquationi)                 \
    macro(glBlendEquationSeparatei)         \
    macro(glBlendFunci)                     \
    macro(glBlendFuncSeparatei)             \
    macro(glDrawArraysIndirect)             \
    macro(glDrawElementsIndirect)           \
    macro(glUniform1d)                      \
    macro(glUniform2d)                      \
    macro(glUniform3d)                      \
    macro(glUniform4d)                      \
    macro(glUniform1dv)                     \
    macro(glUniform2dv)                     \
    macro(glUniform3dv)                     \
    macro(glUniform4dv)                     \
    macro(glUniformMatrix2dv)               \
    macro(glUniformMatrix3dv)               \
    macro(glUniformMatrix4dv)               \
    macro(glUniformMatrix2x3dv)             \
    macro(glUniformMatrix2x4dv)             \
    macro(glUniformMatrix3x2dv)             \
    macro(glUniformMatrix3x4dv)             \
    macro(glUniformMatrix4x2dv)             \
    macro(glUniformMatrix4x3dv)             \
    macro(glGetUniformdv)                   \
    macro(glGetSubroutineUniformLocation)   \
    macro(glGetSubroutineIndex)             \
    macro(glGetActiveSubroutineUniformiv)   \
    macro(glGetActiveSubroutineUniformName) \
    macro(glGetActiveSubroutineName)        \
    macro(glUniformSubroutinesuiv)          \
    macro(glGetUniformSubroutineuiv)        \
    macro(glGetProgramStageiv)              \
    macro(glPatchParameteri)                \
    macro(glPatchParameterfv)               \
    macro(glBindTransformFeedback)          \
    macro(glDeleteTransformFeedbacks)       \
    macro(glGenTransformFeedbacks)          \
    macro(glIsTransformFeedback)            \
    macro(glPauseTransformFeedback)         \
    macro(glResumeTransformFeedback)        \
    macro(glDrawTransformFeedback)          \
    macro(glDrawTransformFeedbackStream)    \
    macro(glBeginQueryIndexed)              \
    macro(glEndQueryIndexed)                \
    macro(glGetQueryIndexediv)

using PFN_glReleaseShaderCompiler     = PFNGLRELEASESHADERCOMPILERPROC;
using PFN_glShaderBinary              = PFNGLSHADERBINARYPROC;
using PFN_glGetShaderPrecisionFormat  = PFNGLGETSHADERPRECISIONFORMATPROC;
using PFN_glDepthRangef               = PFNGLDEPTHRANGEFPROC;
using PFN_glClearDepthf               = PFNGLCLEARDEPTHFPROC;
using PFN_glGetProgramBinary          = PFNGLGETPROGRAMBINARYPROC;
using PFN_glProgramBinary             = PFNGLPROGRAMBINARYPROC;
using PFN_glProgramParameteri         = PFNGLPROGRAMPARAMETERIPROC;
using PFN_glUseProgramStages          = PFNGLUSEPROGRAMSTAGESPROC;
using PFN_glActiveShaderProgram       = PFNGLACTIVESHADERPROGRAMPROC;
using PFN_glCreateShaderProgramv      = PFNGLCREATESHADERPROGRAMVPROC;
using PFN_glBindProgramPipeline       = PFNGLBINDPROGRAMPIPELINEPROC;
using PFN_glDeleteProgramPipelines    = PFNGLDELETEPROGRAMPIPELINESPROC;
using PFN_glGenProgramPipelines       = PFNGLGENPROGRAMPIPELINESPROC;
using PFN_glIsProgramPipeline         = PFNGLISPROGRAMPIPELINEPROC;
using PFN_glGetProgramPipelineiv      = PFNGLGETPROGRAMPIPELINEIVPROC;
using PFN_glProgramUniform1i          = PFNGLPROGRAMUNIFORM1IPROC;
using PFN_glProgramUniform1iv         = PFNGLPROGRAMUNIFORM1IVPROC;
using PFN_glProgramUniform1f          = PFNGLPROGRAMUNIFORM1FPROC;
using PFN_glProgramUniform1fv         = PFNGLPROGRAMUNIFORM1FVPROC;
using PFN_glProgramUniform1d          = PFNGLPROGRAMUNIFORM1DPROC;
using PFN_glProgramUniform1dv         = PFNGLPROGRAMUNIFORM1DVPROC;
using PFN_glProgramUniform1ui         = PFNGLPROGRAMUNIFORM1UIPROC;
using PFN_glProgramUniform1uiv        = PFNGLPROGRAMUNIFORM1UIVPROC;
using PFN_glProgramUniform2i          = PFNGLPROGRAMUNIFORM2IPROC;
using PFN_glProgramUniform2iv         = PFNGLPROGRAMUNIFORM2IVPROC;
using PFN_glProgramUniform2f          = PFNGLPROGRAMUNIFORM2FPROC;
using PFN_glProgramUniform2fv         = PFNGLPROGRAMUNIFORM2FVPROC;
using PFN_glProgramUniform2d          = PFNGLPROGRAMUNIFORM2DPROC;
using PFN_glProgramUniform2dv         = PFNGLPROGRAMUNIFORM2DVPROC;
using PFN_glProgramUniform2ui         = PFNGLPROGRAMUNIFORM2UIPROC;
using PFN_glProgramUniform2uiv        = PFNGLPROGRAMUNIFORM2UIVPROC;
using PFN_glProgramUniform3i          = PFNGLPROGRAMUNIFORM3IPROC;
using PFN_glProgramUniform3iv         = PFNGLPROGRAMUNIFORM3IVPROC;
using PFN_glProgramUniform3f          = PFNGLPROGRAMUNIFORM3FPROC;
using PFN_glProgramUniform3fv         = PFNGLPROGRAMUNIFORM3FVPROC;
using PFN_glProgramUniform3d          = PFNGLPROGRAMUNIFORM3DPROC;
using PFN_glProgramUniform3dv         = PFNGLPROGRAMUNIFORM3DVPROC;
using PFN_glProgramUniform3ui         = PFNGLPROGRAMUNIFORM3UIPROC;
using PFN_glProgramUniform3uiv        = PFNGLPROGRAMUNIFORM3UIVPROC;
using PFN_glProgramUniform4i          = PFNGLPROGRAMUNIFORM4IPROC;
using PFN_glProgramUniform4iv         = PFNGLPROGRAMUNIFORM4IVPROC;
using PFN_glProgramUniform4f          = PFNGLPROGRAMUNIFORM4FPROC;
using PFN_glProgramUniform4fv         = PFNGLPROGRAMUNIFORM4FVPROC;
using PFN_glProgramUniform4d          = PFNGLPROGRAMUNIFORM4DPROC;
using PFN_glProgramUniform4dv         = PFNGLPROGRAMUNIFORM4DVPROC;
using PFN_glProgramUniform4ui         = PFNGLPROGRAMUNIFORM4UIPROC;
using PFN_glProgramUniform4uiv        = PFNGLPROGRAMUNIFORM4UIVPROC;
using PFN_glProgramUniformMatrix2fv   = PFNGLPROGRAMUNIFORMMATRIX2FVPROC;
using PFN_glProgramUniformMatrix3fv   = PFNGLPROGRAMUNIFORMMATRIX3FVPROC;
using PFN_glProgramUniformMatrix4fv   = PFNGLPROGRAMUNIFORMMATRIX4FVPROC;
using PFN_glProgramUniformMatrix2dv   = PFNGLPROGRAMUNIFORMMATRIX2DVPROC;
using PFN_glProgramUniformMatrix3dv   = PFNGLPROGRAMUNIFORMMATRIX3DVPROC;
using PFN_glProgramUniformMatrix4dv   = PFNGLPROGRAMUNIFORMMATRIX4DVPROC;
using PFN_glProgramUniformMatrix2x3fv = PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC;
using PFN_glProgramUniformMatrix3x2fv = PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC;
using PFN_glProgramUniformMatrix2x4fv = PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC;
using PFN_glProgramUniformMatrix4x2fv = PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC;
using PFN_glProgramUniformMatrix3x4fv = PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC;
using PFN_glProgramUniformMatrix4x3fv = PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC;
using PFN_glProgramUniformMatrix2x3dv = PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC;
using PFN_glProgramUniformMatrix3x2dv = PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC;
using PFN_glProgramUniformMatrix2x4dv = PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC;
using PFN_glProgramUniformMatrix4x2dv = PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC;
using PFN_glProgramUniformMatrix3x4dv = PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC;
using PFN_glProgramUniformMatrix4x3dv = PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC;
using PFN_glValidateProgramPipeline   = PFNGLVALIDATEPROGRAMPIPELINEPROC;
using PFN_glGetProgramPipelineInfoLog = PFNGLGETPROGRAMPIPELINEINFOLOGPROC;
using PFN_glVertexAttribL1d           = PFNGLVERTEXATTRIBL1DPROC;
using PFN_glVertexAttribL2d           = PFNGLVERTEXATTRIBL2DPROC;
using PFN_glVertexAttribL3d           = PFNGLVERTEXATTRIBL3DPROC;
using PFN_glVertexAttribL4d           = PFNGLVERTEXATTRIBL4DPROC;
using PFN_glVertexAttribL1dv          = PFNGLVERTEXATTRIBL1DVPROC;
using PFN_glVertexAttribL2dv          = PFNGLVERTEXATTRIBL2DVPROC;
using PFN_glVertexAttribL3dv          = PFNGLVERTEXATTRIBL3DVPROC;
using PFN_glVertexAttribL4dv          = PFNGLVERTEXATTRIBL4DVPROC;
using PFN_glVertexAttribLPointer      = PFNGLVERTEXATTRIBLPOINTERPROC;
using PFN_glGetVertexAttribLdv        = PFNGLGETVERTEXATTRIBLDVPROC;
using PFN_glViewportArrayv            = PFNGLVIEWPORTARRAYVPROC;
using PFN_glViewportIndexedf          = PFNGLVIEWPORTINDEXEDFPROC;
using PFN_glViewportIndexedfv         = PFNGLVIEWPORTINDEXEDFVPROC;
using PFN_glScissorArrayv             = PFNGLSCISSORARRAYVPROC;
using PFN_glScissorIndexed            = PFNGLSCISSORINDEXEDPROC;
using PFN_glScissorIndexedv           = PFNGLSCISSORINDEXEDVPROC;
using PFN_glDepthRangeArrayv          = PFNGLDEPTHRANGEARRAYVPROC;
using PFN_glDepthRangeIndexed         = PFNGLDEPTHRANGEINDEXEDPROC;
using PFN_glGetFloati_v               = PFNGLGETFLOATI_VPROC;
using PFN_glGetDoublei_v              = PFNGLGETDOUBLEI_VPROC;

#define APPLY_MACRO_TO_GL_API_4_1(macro) \
    macro(glReleaseShaderCompiler)       \
    macro(glShaderBinary)                \
    macro(glGetShaderPrecisionFormat)    \
    macro(glDepthRangef)                 \
    macro(glClearDepthf)                 \
    macro(glGetProgramBinary)            \
    macro(glProgramBinary)               \
    macro(glProgramParameteri)           \
    macro(glUseProgramStages)            \
    macro(glActiveShaderProgram)         \
    macro(glCreateShaderProgramv)        \
    macro(glBindProgramPipeline)         \
    macro(glDeleteProgramPipelines)      \
    macro(glGenProgramPipelines)         \
    macro(glIsProgramPipeline)           \
    macro(glGetProgramPipelineiv)        \
    macro(glProgramUniform1i)            \
    macro(glProgramUniform1iv)           \
    macro(glProgramUniform1f)            \
    macro(glProgramUniform1fv)           \
    macro(glProgramUniform1d)            \
    macro(glProgramUniform1dv)           \
    macro(glProgramUniform1ui)           \
    macro(glProgramUniform1uiv)          \
    macro(glProgramUniform2i)            \
    macro(glProgramUniform2iv)           \
    macro(glProgramUniform2f)            \
    macro(glProgramUniform2fv)           \
    macro(glProgramUniform2d)            \
    macro(glProgramUniform2dv)           \
    macro(glProgramUniform2ui)           \
    macro(glProgramUniform2uiv)          \
    macro(glProgramUniform3i)            \
    macro(glProgramUniform3iv)           \
    macro(glProgramUniform3f)            \
    macro(glProgramUniform3fv)           \
    macro(glProgramUniform3d)            \
    macro(glProgramUniform3dv)           \
    macro(glProgramUniform3ui)           \
    macro(glProgramUniform3uiv)          \
    macro(glProgramUniform4i)            \
    macro(glProgramUniform4iv)           \
    macro(glProgramUniform4f)            \
    macro(glProgramUniform4fv)           \
    macro(glProgramUniform4d)            \
    macro(glProgramUniform4dv)           \
    macro(glProgramUniform4ui)           \
    macro(glProgramUniform4uiv)          \
    macro(glProgramUniformMatrix2fv)     \
    macro(glProgramUniformMatrix3fv)     \
    macro(glProgramUniformMatrix4fv)     \
    macro(glProgramUniformMatrix2dv)     \
    macro(glProgramUniformMatrix3dv)     \
    macro(glProgramUniformMatrix4dv)     \
    macro(glProgramUniformMatrix2x3fv)   \
    macro(glProgramUniformMatrix3x2fv)   \
    macro(glProgramUniformMatrix2x4fv)   \
    macro(glProgramUniformMatrix4x2fv)   \
    macro(glProgramUniformMatrix3x4fv)   \
    macro(glProgramUniformMatrix4x3fv)   \
    macro(glProgramUniformMatrix2x3dv)   \
    macro(glProgramUniformMatrix3x2dv)   \
    macro(glProgramUniformMatrix2x4dv)   \
    macro(glProgramUniformMatrix4x2dv)   \
    macro(glProgramUniformMatrix3x4dv)   \
    macro(glProgramUniformMatrix4x3dv)   \
    macro(glValidateProgramPipeline)     \
    macro(glGetProgramPipelineInfoLog)   \
    macro(glVertexAttribL1d)             \
    macro(glVertexAttribL2d)             \
    macro(glVertexAttribL3d)             \
    macro(glVertexAttribL4d)             \
    macro(glVertexAttribL1dv)            \
    macro(glVertexAttribL2dv)            \
    macro(glVertexAttribL3dv)            \
    macro(glVertexAttribL4dv)            \
    macro(glVertexAttribLPointer)        \
    macro(glGetVertexAttribLdv)          \
    macro(glViewportArrayv)              \
    macro(glViewportIndexedf)            \
    macro(glViewportIndexedfv)           \
    macro(glScissorArrayv)               \
    macro(glScissorIndexed)              \
    macro(glScissorIndexedv)             \
    macro(glDepthRangeArrayv)            \
    macro(glDepthRangeIndexed)           \
    macro(glGetFloati_v)                 \
    macro(glGetDoublei_v)

using PFN_glDrawArraysInstancedBaseInstance             = PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC;
using PFN_glDrawElementsInstancedBaseInstance           = PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC;
using PFN_glDrawElementsInstancedBaseVertexBaseInstance = PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC;
using PFN_glGetInternalformativ                         = PFNGLGETINTERNALFORMATIVPROC;
using PFN_glGetActiveAtomicCounterBufferiv              = PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC;
using PFN_glBindImageTexture                            = PFNGLBINDIMAGETEXTUREPROC;
using PFN_glMemoryBarrier                               = PFNGLMEMORYBARRIERPROC;
using PFN_glTexStorage1D                                = PFNGLTEXSTORAGE1DPROC;
using PFN_glTexStorage2D                                = PFNGLTEXSTORAGE2DPROC;
using PFN_glTexStorage3D                                = PFNGLTEXSTORAGE3DPROC;
using PFN_glDrawTransformFeedbackInstanced              = PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC;
using PFN_glDrawTransformFeedbackStreamInstanced        = PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC;

#define APPLY_MACRO_TO_GL_API_4_2(macro)                 \
    macro(glDrawArraysInstancedBaseInstance)             \
    macro(glDrawElementsInstancedBaseInstance)           \
    macro(glDrawElementsInstancedBaseVertexBaseInstance) \
    macro(glGetInternalformativ)                         \
    macro(glGetActiveAtomicCounterBufferiv)              \
    macro(glBindImageTexture)                            \
    macro(glMemoryBarrier)                               \
    macro(glTexStorage1D)                                \
    macro(glTexStorage2D)                                \
    macro(glTexStorage3D)                                \
    macro(glDrawTransformFeedbackInstanced)              \
    macro(glDrawTransformFeedbackStreamInstanced)

using PFN_glClearBufferData                 = PFNGLCLEARBUFFERDATAPROC;
using PFN_glClearBufferSubData              = PFNGLCLEARBUFFERSUBDATAPROC;
using PFN_glDispatchCompute                 = PFNGLDISPATCHCOMPUTEPROC;
using PFN_glDispatchComputeIndirect         = PFNGLDISPATCHCOMPUTEINDIRECTPROC;
using PFN_glCopyImageSubData                = PFNGLCOPYIMAGESUBDATAPROC;
using PFN_glFramebufferParameteri           = PFNGLFRAMEBUFFERPARAMETERIPROC;
using PFN_glGetFramebufferParameteriv       = PFNGLGETFRAMEBUFFERPARAMETERIVPROC;
using PFN_glGetInternalformati64v           = PFNGLGETINTERNALFORMATI64VPROC;
using PFN_glInvalidateTexSubImage           = PFNGLINVALIDATETEXSUBIMAGEPROC;
using PFN_glInvalidateTexImage              = PFNGLINVALIDATETEXIMAGEPROC;
using PFN_glInvalidateBufferSubData         = PFNGLINVALIDATEBUFFERSUBDATAPROC;
using PFN_glInvalidateBufferData            = PFNGLINVALIDATEBUFFERDATAPROC;
using PFN_glInvalidateFramebuffer           = PFNGLINVALIDATEFRAMEBUFFERPROC;
using PFN_glInvalidateSubFramebuffer        = PFNGLINVALIDATESUBFRAMEBUFFERPROC;
using PFN_glMultiDrawArraysIndirect         = PFNGLMULTIDRAWARRAYSINDIRECTPROC;
using PFN_glMultiDrawElementsIndirect       = PFNGLMULTIDRAWELEMENTSINDIRECTPROC;
using PFN_glGetProgramInterfaceiv           = PFNGLGETPROGRAMINTERFACEIVPROC;
using PFN_glGetProgramResourceIndex         = PFNGLGETPROGRAMRESOURCEINDEXPROC;
using PFN_glGetProgramResourceName          = PFNGLGETPROGRAMRESOURCENAMEPROC;
using PFN_glGetProgramResourceiv            = PFNGLGETPROGRAMRESOURCEIVPROC;
using PFN_glGetProgramResourceLocation      = PFNGLGETPROGRAMRESOURCELOCATIONPROC;
using PFN_glGetProgramResourceLocationIndex = PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC;
using PFN_glShaderStorageBlockBinding       = PFNGLSHADERSTORAGEBLOCKBINDINGPROC;
using PFN_glTexBufferRange                  = PFNGLTEXBUFFERRANGEPROC;
using PFN_glTexStorage2DMultisample         = PFNGLTEXSTORAGE2DMULTISAMPLEPROC;
using PFN_glTexStorage3DMultisample         = PFNGLTEXSTORAGE3DMULTISAMPLEPROC;
using PFN_glTextureView                     = PFNGLTEXTUREVIEWPROC;
using PFN_glBindVertexBuffer                = PFNGLBINDVERTEXBUFFERPROC;
using PFN_glVertexAttribFormat              = PFNGLVERTEXATTRIBFORMATPROC;
using PFN_glVertexAttribIFormat             = PFNGLVERTEXATTRIBIFORMATPROC;
using PFN_glVertexAttribLFormat             = PFNGLVERTEXATTRIBLFORMATPROC;
using PFN_glVertexAttribBinding             = PFNGLVERTEXATTRIBBINDINGPROC;
using PFN_glVertexBindingDivisor            = PFNGLVERTEXBINDINGDIVISORPROC;
using PFN_glDebugMessageControl             = PFNGLDEBUGMESSAGECONTROLPROC;
using PFN_glDebugMessageInsert              = PFNGLDEBUGMESSAGEINSERTPROC;
using PFN_glDebugMessageCallback            = PFNGLDEBUGMESSAGECALLBACKPROC;
using PFN_glGetDebugMessageLog              = PFNGLGETDEBUGMESSAGELOGPROC;
using PFN_glPushDebugGroup                  = PFNGLPUSHDEBUGGROUPPROC;
using PFN_glPopDebugGroup                   = PFNGLPOPDEBUGGROUPPROC;
using PFN_glObjectLabel                     = PFNGLOBJECTLABELPROC;
using PFN_glGetObjectLabel                  = PFNGLGETOBJECTLABELPROC;
using PFN_glObjectPtrLabel                  = PFNGLOBJECTPTRLABELPROC;
using PFN_glGetObjectPtrLabel               = PFNGLGETOBJECTPTRLABELPROC;

#define APPLY_MACRO_TO_GL_API_4_3(macro)     \
    macro(glClearBufferData)                 \
    macro(glClearBufferSubData)              \
    macro(glDispatchCompute)                 \
    macro(glDispatchComputeIndirect)         \
    macro(glCopyImageSubData)                \
    macro(glFramebufferParameteri)           \
    macro(glGetFramebufferParameteriv)       \
    macro(glGetInternalformati64v)           \
    macro(glInvalidateTexSubImage)           \
    macro(glInvalidateTexImage)              \
    macro(glInvalidateBufferSubData)         \
    macro(glInvalidateBufferData)            \
    macro(glInvalidateFramebuffer)           \
    macro(glInvalidateSubFramebuffer)        \
    macro(glMultiDrawArraysIndirect)         \
    macro(glMultiDrawElementsIndirect)       \
    macro(glGetProgramInterfaceiv)           \
    macro(glGetProgramResourceIndex)         \
    macro(glGetProgramResourceName)          \
    macro(glGetProgramResourceiv)            \
    macro(glGetProgramResourceLocation)      \
    macro(glGetProgramResourceLocationIndex) \
    macro(glShaderStorageBlockBinding)       \
    macro(glTexBufferRange)                  \
    macro(glTexStorage2DMultisample)         \
    macro(glTexStorage3DMultisample)         \
    macro(glTextureView)                     \
    macro(glBindVertexBuffer)                \
    macro(glVertexAttribFormat)              \
    macro(glVertexAttribIFormat)             \
    macro(glVertexAttribLFormat)             \
    macro(glVertexAttribBinding)             \
    macro(glVertexBindingDivisor)            \
    macro(glDebugMessageControl)             \
    macro(glDebugMessageInsert)              \
    macro(glDebugMessageCallback)            \
    macro(glGetDebugMessageLog)              \
    macro(glPushDebugGroup)                  \
    macro(glPopDebugGroup)                   \
    macro(glObjectLabel)                     \
    macro(glGetObjectLabel)                  \
    macro(glObjectPtrLabel)                  \
    macro(glGetObjectPtrLabel)

#define APPLY_MACRO_TO_GL_API(macro) \
    APPLY_MACRO_TO_GL_API_1_2(macro) \
    APPLY_MACRO_TO_GL_API_1_3(macro) \
    APPLY_MACRO_TO_GL_API_1_4(macro) \
    APPLY_MACRO_TO_GL_API_1_5(macro) \
    APPLY_MACRO_TO_GL_API_2_0(macro) \
    APPLY_MACRO_TO_GL_API_2_1(macro) \
    APPLY_MACRO_TO_GL_API_3_0(macro) \
    APPLY_MACRO_TO_GL_API_3_1(macro) \
    APPLY_MACRO_TO_GL_API_3_2(macro) \
    APPLY_MACRO_TO_GL_API_3_3(macro) \
    APPLY_MACRO_TO_GL_API_4_1(macro) \
    APPLY_MACRO_TO_GL_API_4_2(macro) \
    APPLY_MACRO_TO_GL_API_4_3(macro)

#define DEFINE_GL_API_FUNCTION_PTR_MACRO(function) PFN_##function function;

class GlSample : public Sample
{
public:
    GlSample (std::wstring const& title, uint32_t width, uint32_t height);

    virtual ~GlSample ();

    void onInit (HINSTANCE instance, HWND window, HDC deviceContext) override;

    void onExit () override;

protected:
    APPLY_MACRO_TO_GL_API(DEFINE_GL_API_FUNCTION_PTR_MACRO)

    GLuint createShader (GLenum type, const char *code);

    GLuint createProgram (GLuint vertShader, GLuint fragShader);

protected:
    HGLRC mRenderContext;
};

#endif
