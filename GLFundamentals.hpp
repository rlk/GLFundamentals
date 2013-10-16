// Copyright (c) 2013 Robert Kooima
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef GLFUNDAMENTALS_HPP
#define GLFUNDAMENTALS_HPP

/// This header provides the basic functionality necessary to make effective use
/// of modern OpenGL (e.g. OpenGL 3.2 Core Profile or OpenGL ES 2.0 or later).
///
/// Given the lack of fixed functionality and matrix handling, all applications
/// will need to load and compile shaders and perform matrix arithmetic. Thus,
/// these capabilities are provided here.

//------------------------------------------------------------------------------

#ifdef __APPLE__
#  include <OpenGL/gl3.h>
#else
#  include <GL/glew.h>
#endif

#include <cstdlib>
#include <cstdio>
#include <cmath>

//------------------------------------------------------------------------------

#define GL_CHECK_ERROR() check(__FILE__, __LINE__)

namespace gl
{
    inline void check(const char *file, int line, FILE *fp = stderr)
    {
        switch (glGetError())
        {
        case GL_INVALID_ENUM:
            fprintf(fp, "%s:%d: Invalid Enum\n",      file, line); abort();
        case GL_INVALID_VALUE:
            fprintf(fp, "%s:%d: Invalid Value\n",     file, line); abort();
        case GL_INVALID_OPERATION:
            fprintf(fp, "%s:%d: Invalid Operation\n", file, line); abort();
        case GL_OUT_OF_MEMORY:
            fprintf(fp, "%s:%d: Out of Memory\n",     file, line); abort();
        }
    }

    //--------------------------------------------------------------------------

    /// 3-component 32-bit floating point vector.

    struct vec3
    {
        GLfloat v[3];

        vec3()
        {
            v[0] = 0;
            v[1] = 0;
            v[2] = 0;
        }
        vec3(GLfloat x, GLfloat y, GLfloat z)
        {
            v[0] = x;
            v[1] = y;
            v[2] = z;
        }

        const GLfloat& operator[](int i) const { return v[i]; }
              GLfloat& operator[](int i)       { return v[i]; }
    };

    //--------------------------------------------------------------------------

    /// 4-component 32-bit floating point vector.

    struct vec4
    {
        GLfloat v[4];

        vec4()
        {
            v[0] = 0;
            v[1] = 0;
            v[2] = 0;
            v[3] = 0;
        }
        vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
        {
            v[0] = x;
            v[1] = y;
            v[2] = z;
            v[3] = w;
        }

        const GLfloat& operator[](int i) const { return v[i]; }
              GLfloat& operator[](int i)       { return v[i]; }
    };

    //--------------------------------------------------------------------------

    /// Row-wise 3x3 32-bit floating point matrix.

    struct mat3
    {
        vec3 M[3];

        mat3()
        {
            M[0] = vec3(1, 0, 0);
            M[1] = vec3(0, 1, 0);
            M[2] = vec3(0, 0, 1);
        }
        mat3(GLfloat m00, GLfloat m01, GLfloat m02,
             GLfloat m10, GLfloat m11, GLfloat m12,
             GLfloat m20, GLfloat m21, GLfloat m22)
        {
            M[0] = vec3(m00, m01, m02);
            M[1] = vec3(m10, m11, m12);
            M[2] = vec3(m20, m21, m22);
        }

        const vec3& operator[](int i) const { return M[i]; }
              vec3& operator[](int i)       { return M[i]; }

        operator const GLfloat*() const
        {
            return const_cast<GLfloat *>(&M[0][0]);
        }
    };

    //--------------------------------------------------------------------------

    /// Row-wise 4x4 32-bit floating point matrix.

    struct mat4
    {
        vec4 M[4];

        mat4()
        {
            M[0] = vec4(1, 0, 0, 0);
            M[1] = vec4(0, 1, 0, 0);
            M[2] = vec4(0, 0, 1, 0);
            M[3] = vec4(0, 0, 0, 1);
        }
        mat4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
             GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
             GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
             GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33)
        {
            M[0] = vec4(m00, m01, m02, m03);
            M[1] = vec4(m10, m11, m12, m13);
            M[2] = vec4(m20, m21, m22, m23);
            M[3] = vec4(m30, m31, m32, m33);
        }

        const vec4& operator[](int i) const { return M[i]; }
              vec4& operator[](int i)       { return M[i]; }

        operator const GLfloat*() const
        {
            return const_cast<GLfloat *>(&M[0][0]);
        }
    };

    //--------------------------------------------------------------------------

    /// Convert an angle in degrees to an angle in radians.

    inline GLfloat to_radians(GLfloat degrees)
    {
        return degrees * 0.01745329;
    }

    /// Convent an angle in radians to an angle in degrees.

    inline GLfloat to_degrees(GLfloat radians)
    {
        return radians * 57.2957795;
    }

    /// Calculate the 3-component sum of v and w.

    inline vec3 operator+(const vec3& v, const vec3& w)
    {
        return vec3(v[0] + w[0], v[1] + w[1], v[2] + w[2]);
    }

    /// Calculate the 3-component difference of v and w.

    inline vec3 operator-(const vec3& v, const vec3& w)
    {
        return vec3(v[0] - w[0], v[1] - w[1], v[2] - w[2]);
    }

    /// Calculate the 3-component scalar quotient of v and k.

    inline vec3 operator/(const vec3& v, GLfloat k)
    {
        return vec3(v[0] / k, v[1] / k, v[2] / k);
    }

    /// Calculate the 3-component scalar product of v and k.

    inline vec3 operator*(const vec3& v, GLfloat k)
    {
        return vec3(v[0] * k, v[1] * k, v[2] * k);
    }

    /// Calculate the 3-component dot product of v and w.

    inline GLfloat operator*(const vec3& v, const vec3& w)
    {
        return v[0] * w[0] + v[1] * w[1] + v[2] * w[2];
    }

    /// Calculate the 4-component dot product of v and w.

    inline GLfloat operator*(const vec4& v, const vec4& w)
    {
        return v[0] * w[0] + v[1] * w[1] + v[2] * w[2] + v[3] * w[3];
    }

    /// Calculate the 3-component transform of vector v by matrix A.

    inline vec3 operator*(const mat3& A, const vec3& v)
    {
        return vec3(A[0] * v, A[1] * v, A[2] * v);
    }

    /// Calculate the 4-component transform of vector v by matrix A.

    inline vec4 operator*(const mat4& A, const vec4& v)
    {
        return vec4(A[0] * v, A[1] * v, A[2] * v, A[3] * v);
    }

    /// Calculate the 3x3 matrix product of A and B.

    inline mat3 operator*(const mat3& A, const mat3& B)
    {
        mat3 M;
        for     (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                M[i][j] = A[i][0] * B[0][j]
                        + A[i][1] * B[1][j]
                        + A[i][2] * B[2][j];
        return M;
    }

    /// Calculate the 4x4 matrix product of A and B.

    inline mat4 operator*(const mat4& A, const mat4& B)
    {
        mat4 M;
        for     (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                M[i][j] = A[i][0] * B[0][j]
                        + A[i][1] * B[1][j]
                        + A[i][2] * B[2][j]
                        + A[i][3] * B[3][j];
        return M;
    }

    //--------------------------------------------------------------------------

    /// Compute the length of vector v.

    inline GLfloat length(const vec3 &v)
    {
        return sqrt(v * v);
    }

    /// Compute the cross product of vectors v and w.

    inline vec3 cross(const vec3& v, const vec3& w)
    {
        return vec3(v[1] * w[2] - v[2] * w[1],
                    v[2] * w[0] - v[0] * w[2],
                    v[0] * w[1] - v[1] * w[0]);
    }

    /// Compute the normalization of vector v.

    inline vec3 normalize(const vec3& v)
    {
        return v / length(v);
    }

    /// Return a matrix giving a rotation about X through a radians.

    inline mat4 xrotation(GLfloat a)
    {
        return mat4(1, 0,       0,      0,
                    0, cos(a), -sin(a), 0,
                    0, sin(a),  cos(a), 0,
                    0, 0,       0,      1);
    }

    /// Return a matrix giving a rotation about Y through a radians.

    inline mat4 yrotation(GLfloat a)
    {
        return mat4( cos(a), 0, sin(a), 0,
                     0,      1, 0,      0,
                    -sin(a), 0, cos(a), 0,
                     0,      0, 0,      1);
    }

    /// Return a matrix giving a rotation about Z through a radians.

    inline mat4 zrotation(GLfloat a)
    {
        return mat4(cos(a), -sin(a), 0, 0,
                    sin(a),  cos(a), 0, 0,
                    0,       0,      1, 0,
                    0,       0,      0, 1);
    }

    /// Return a matrix giving a translation along vector v.

    inline mat4 translation(const vec3& v)
    {
        return mat4(1, 0, 0, v[0],
                    0, 1, 0, v[1],
                    0, 0, 1, v[2],
                    0, 0, 0, 1);
    }

    /// Return a matrix giving a scale along vector v.

    inline mat4 scale(const vec3& v)
    {
        return mat4(v[0], 0,    0,    0,
                    0,    v[1], 0,    0,
                    0,    0,    v[2], 0,
                    0,    0,    0,    1);
    }

    /// Return a matrix giving a perspective projection with field-of-view v,
    /// aspect ratio a, near clipping distance n, and far clipping distance f.

    inline mat4 perspective(GLfloat v, GLfloat a, GLfloat n, GLfloat f)
    {
        const GLfloat y = n * tan(v / 2);
        const GLfloat x = y * a;

        return mat4(n / x, 0, 0, 0, 0,
                    n / y, 0, 0, 0, 0, (n + f) / (n - f),
                                   2 * (n * f) / (n - f), 0, 0, -1, 0);
    }

    /// Return a matrix giving a perspective projection with the given left,
    /// right, bottom, top, near, and far clipping boundaries.

    inline mat4 perspective(GLfloat l, GLfloat r,
                            GLfloat b, GLfloat t,
                            GLfloat n, GLfloat f)
    {
        return mat4((n + n) / (r - l), 0,
                    (r + l) / (r - l), 0, 0,
                    (n + n) / (t - b),
                    (t + b) / (t - b), 0, 0, 0,
                    (n + f) / (n - f),
                2 * (n * f) / (n - f), 0, 0, -1, 0);
    }

    /// Return a matrix giving an orthogonal projection with the given left,
    /// right, bottom, top, near, and far clipping boundaries.

    inline mat4 orthogonal(GLfloat l, GLfloat r,
                           GLfloat b, GLfloat t,
                           GLfloat n, GLfloat f)
    {
         return mat4(2 / (r - l), 0, 0, -(r + l) / (r - l), 0,
                     2 / (t - b), 0,    -(t + b) / (t - b), 0, 0,
                    -2 / (f - n),       -(f + n) / (f - n), 0, 0, 0, 1);
    }

    /// Compute a normal matrix for the given model-view matrix by returning
    /// the transposed inverse upper 3x3 matrix of the given 4x4 matrix.

    inline mat3 normal(const mat4& M)
    {
        const GLfloat d = M[0][0] * M[1][1] * M[2][2]
                        - M[0][0] * M[1][2] * M[2][1]
                        + M[0][1] * M[1][2] * M[2][0]
                        - M[0][1] * M[1][0] * M[2][2]
                        + M[0][2] * M[1][0] * M[2][1]
                        - M[0][2] * M[1][1] * M[2][0];
        if (fabs(d) > 0.f)
            return mat3(-M[1][2] * M[2][1] + M[1][1] * M[2][2],
                         M[1][2] * M[2][0] - M[1][0] * M[2][2],
                        -M[1][1] * M[2][0] + M[1][0] * M[2][1],
                         M[0][2] * M[2][1] - M[0][1] * M[2][2],
                        -M[0][2] * M[2][0] + M[0][0] * M[2][2],
                         M[0][1] * M[2][0] - M[0][0] * M[2][1],
                        -M[0][2] * M[1][1] + M[0][1] * M[1][2],
                         M[0][2] * M[1][0] - M[0][0] * M[1][2],
                        -M[0][1] * M[1][0] + M[0][0] * M[1][1]);
        else
            return mat3();
    }

    //--------------------------------------------------------------------------

    /// Load the named file into a newly-allocated buffer. Append nul.

    inline char *read_shader_source(const char *name)
    {
        FILE *fp = 0;
        void  *p = 0;
        size_t n = 0;

        if ((fp = fopen(name, "rb")))
        {
            if (fseek(fp, 0, SEEK_END) == 0)
            {
                if ((n = (size_t) ftell(fp)))
                {
                    if (fseek(fp, 0, SEEK_SET) == 0)
                    {
                        if ((p = calloc(n + 1, 1)))
                        {
                            fread(p, 1, n, fp);
                        }
                    }
                }
            }
            fclose(fp);
        }
        else fprintf(stderr, "Failed to open '%s'.\n", name);

        return (char *) p;
    }

    /// Check the shader compile status. If failed, print the log. Return status.

    inline bool report_shader_status(GLuint shader, FILE *fp = stderr)
    {
        GLchar *p = 0;
        GLint   s = 0;
        GLint   n = 0;

        glGetShaderiv(shader, GL_COMPILE_STATUS,  &s);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &n);

        if (s == 0)
        {
            if ((p = (GLchar *) calloc(n + 1, 1)))
            {
                glGetShaderInfoLog(shader, n, NULL, p);

                fprintf(fp, "Shader Error:\n%s", p);
                free(p);
            }
            return false;
        }
        return true;
    }

    /// Check the program link status. If failed, print the log. Return status.

    inline bool report_program_status(GLuint program, FILE *fp = stderr)
    {
        GLchar *p = 0;
        GLint   s = 0;
        GLint   n = 0;

        glGetProgramiv(program, GL_LINK_STATUS,     &s);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &n);

        if (s == 0)
        {
            if ((p = (GLchar *) calloc(n + 1, 1)))
            {
                glGetProgramInfoLog(program, n, NULL, p);

                fprintf(fp, "Program Error:\n%s", p);
                free(p);
            }
            return false;
        }
        return true;
    }

    /// Compile and return a new shader of the given type using the given GLSL
    /// source string. Return 0 on failure.

    inline GLuint init_shader(GLenum type, const char *source)
    {
        GLuint shader = glCreateShader(type);

        if (shader)
        {
            glShaderSource (shader, 1, (const GLchar **) &source, NULL);
            glCompileShader(shader);

            if (report_shader_status(shader))
                return shader;
            else
                glDeleteShader(shader);
        }
        return 0;
    }

    /// Link and return a new program object with the given vertex and fragment
    /// shader objects. Return 0 on failure.

    inline GLuint init_program(GLuint vert_shader, GLuint frag_shader)
    {
        GLuint program = glCreateProgram();

        if (program)
        {
            glAttachShader(program, vert_shader);
            glAttachShader(program, frag_shader);

            glLinkProgram(program);

            if (report_program_status(program))
                return program;
            else
                glDeleteProgram(program);
        }
        return 0;
    }

    /// Initialize and return an OpenGL program object using the named vertex
    /// and fragment shader source files. Return 0 on failure.

    inline GLuint init_program(const char *vert_name,
                               const char *frag_name)
    {
        GLuint program = 0;

        char *vert_source = read_shader_source(vert_name);
        char *frag_source = read_shader_source(frag_name);

        if (vert_source && frag_source)
        {
            GLuint vert_shader = init_shader(GL_VERTEX_SHADER,   vert_source);
            GLuint frag_shader = init_shader(GL_FRAGMENT_SHADER, frag_source);

            if (vert_shader && frag_shader)
                program = init_program(vert_shader, frag_shader);

            glDeleteShader(frag_shader);
            glDeleteShader(vert_shader);
        }

        free(frag_source);
        free(vert_source);

        return program;
    }

    //--------------------------------------------------------------------------
}

#endif
