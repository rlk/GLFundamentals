# GLFundamentals

GLFundamentals is C++ header that provides the basic functionality necessary to make effective use of modern OpenGL (e.g. OpenGL 3.2 Core Profile or OpenGL ES 2.0 or later).

Given the lack of fixed functionality and matrix handling, all applications will need to load and compile shaders and perform matrix arithmetic. Thus, these capabilities are provided here.

Basic TGA read and write procedures for texture handling are also provided.

All of the following symbols are defined in the `gl` namespace.

## Types

### 2-vector

`struct vec2` represents a 2-component vector of `GLfloat` values.

- Constructor initializing to (x, y). Default is (0, 0).

        vec3(GLfloat x=0, GLfloat y=0)

- Accessors giving array-like subscripting.

        const GLfloat& operator[](int i) const
              GLfloat& operator[](int i)

- Cast to float.

        operator const GLfloat*() const

### 3-vector

`struct vec3` represents a 3-component vector of `GLfloat` values.

- Constructor initializing to (x, y, z). Default is (0, 0, 0).

        vec3(GLfloat x=0, GLfloat y=0, GLfloat z=0)

- Accessors giving array-like subscripting.

        const GLfloat& operator[](int i) const
              GLfloat& operator[](int i)

- Cast to float.

        operator const GLfloat*() const

### 4-vector

`struct vec4` represents a 4-component vector of `GLfloat` values.

- Constructor initializing to (x, y, z, w). Default is (0, 0, 0, 0).

        vec4(GLfloat x=0, GLfloat y=0, GLfloat z=0, GLfloat w=0)

- Array-like subscript accessors returning scalar values.

        const GLfloat& operator[](int i) const
              GLfloat& operator[](int i)

- Cast to float

        operator const GLfloat*() const

### 3-matrix

`struct mat3` represents a 3x3 matrix of `GLfloat` values.

- Constructor. Default is the identity.

        mat3(GLfloat m00=1, GLfloat m01=0, GLfloat m02=0,
             GLfloat m10=0, GLfloat m11=1, GLfloat m12=0,
             GLfloat m20=0, GLfloat m21=0, GLfloat m22=1)

- Array-like subscript accessors returning vec3 row vectors.

        const vec3& operator[](int i) const
              vec3& operator[](int i)

    The `vec3` type implements the same subscript accessor. Thus `M[i][j]` is a valid reference to the matrix element at row `i` column `j`.

- Cast to float giving row-order matrix data.

        operator const GLfloat*() const

    This cast allows 3x3 matrices to be applied directly to program uniforms. As the internal matrix representation is row-wise, pass `GL_TRUE` to the transpose argument.

        mat3 N;
        glUniformMatrix3fv(location, 1, GL_TRUE, N);

### 4-matrix

`struct mat4` represents a 4x4 matrix of `GLfloat` values.

- Constructor. Default is the identity.

        mat4(GLfloat m00=1, GLfloat m01=0, GLfloat m02=0, GLfloat m03=0,
             GLfloat m10=0, GLfloat m11=1, GLfloat m12=0, GLfloat m13=0,
             GLfloat m20=0, GLfloat m21=0, GLfloat m22=1, GLfloat m23=0,
             GLfloat m30=0, GLfloat m31=0, GLfloat m32=0, GLfloat m33=1)

- Array-like subscript accessors returning vec4 row vectors.

        const vec4& operator[](int i) const
              vec4& operator[](int i)

    The `vec4` type implements the same subscript accessor. Thus `M[i][j]` is a valid reference to the matrix element at row `i` column `j`.

- Cast to float giving row-order matrix data.

        operator const GLfloat*() const

    This cast allows 4x4 matrices to be applied directly to program uniforms. As the internal matrix representation is row-wise, pass `GL_TRUE` to the transpose argument.

        mat4 M;
        glUniformMatrix4fv(location, 1, GL_TRUE, M);

## Functions

### Convenience functions

- Convert an angle in degrees to an angle in radians.

        GLfloat to_radians(GLfloat degrees)

- Convert an angle in radians to an angle in degrees.

        GLfloat to_degrees(GLfloat radians)

- If `glGetError()` is not `GL_NO_ERROR` then print a message to `stderr` and abort. Users may define `NDEBUG` to eliminate all checks.

        GL_CHECK_ERROR()

### Vector-matrix Operations

- Compute the 3-component sum of `v` and `w`.

        vec3 operator+(const vec3& v, const vec3& w)

- Compute the 3-component difference of `v` and `w`.

        vec3 operator-(const vec3& v, const vec3& w)

- Compute the 3-component scalar quotient of `v` and `k`.

        vec3 operator/(const vec3& v, GLfloat k)

- Compute the 3-component scalar product of `v` and `k`.

        vec3 operator*(const vec3& v, GLfloat k)

- Compute the 3-component dot product of `v` and `w`.

        GLfloat operator*(const vec3& v, const vec3& w)

- Compute the 4-component dot product of `v` and `w`.

        GLfloat operator*(const vec4& v, const vec4& w)

- Compute the 3-component transform of vector `v` by matrix `A`.

        vec3 operator*(const mat3& A, const vec3& v)

- Compute the 4-component transform of vector `v` by matrix `A`.

        vec4 operator*(const mat4& A, const vec4& v)

- Compute the 3x3 matrix product of `A` and `B`.

        mat3 operator*(const mat3& A, const mat3& B)

- Compute the 4x4 matrix product of `A` and `B`.

        mat4 operator*(const mat4& A, const mat4& B)

- Return the transpose of a 3x3 matrix `A`.

        mat3 transpose(const mat3& A)

- Return the transpose of a 4x4 matrix `A`.

        mat4 transpose(const mat4& A)

- Return the inverse of a 4x4 matrix `A`.

        mat4 inverse(const mat4& A)

- Compute the length of vector `v`.

        GLfloat length(const vec3 &v)

- Compute the cross product of vectors `v` and `w`.

        vec3 cross(const vec3& v, const vec3& w)

- Compute the normalization of vector `v`.

        vec3 normalize(const vec3& v)

### Transformations

- Return a matrix giving a rotation about the X axis through `a` radians.

        mat4 xrotation(GLfloat a)

- Return a matrix giving a rotation about the Y axis through `a` radians.

        mat4 yrotation(GLfloat a)

- Return a matrix giving a rotation about the Z axis through `a` radians.

        mat4 zrotation(GLfloat a)

- Return a matrix giving a rotation about vector `v` through `a` radians.

        mat4 rotation(const vec3& v, GLfloat a)

- Return a matrix giving a translation along vector `v`.

        mat4 translation(const vec3& v)

- Return a matrix giving a scale along vector `v`.

        mat4 scale(const vec3& v)

- Return a matrix giving a perspective projection with field-of-view `v` in radians, aspect ratio `a`, near clipping distance `n`, and far clipping distance `f`.

        mat4 perspective(GLfloat v, GLfloat a, GLfloat n, GLfloat f)

- Return a matrix giving a perspective projection with the given left, right, bottom, top, near, and far clipping boundaries.

        mat4 perspective(GLfloat l, GLfloat r,
                         GLfloat b, GLfloat t,
                         GLfloat n, GLfloat f)

- Return a matrix giving an orthogonal projection with the given left, right, bottom, top, near, and far clipping boundaries.

        mat4 orthogonal(GLfloat l, GLfloat r,
                        GLfloat b, GLfloat t,
                        GLfloat n, GLfloat f)

- Compute a normal matrix for the given model-view matrix by returning the transposed inverse upper 3x3 matrix of the given 4x4 matrix.

        mat3 normal(const mat4& M)

### Image Functions

- Read a 24 or 32-bit uncompressed true-color Targa image file (TGA). Return a pointer to the raw pixels. Give width, height, and depth in `w`, `h`, `d`. Return null on failure.

        void *read_tga(const char *filename, int& w, int& h, int& d)

- Write a 24 or 32-bit uncompressed true-color Targa image file (TGA). Receive the raw pixel buffer in `p`. Receive width, height, and depth in `w`, `h`, and `d`. Return 0 on success and -1 on failure. `errno` indicates the error.

        int write_tga(const char *filename, int w, int h, int d, void *p)

### Shader Functions

The following functions implement a shader loader and compiler with error reporting, plus a program linker. Most applications will need only to call `init_program` with their vertex and fragment shader file names, receiving a `GLuint` program object in return. The rest of these functions may be used if the default behavior of `init_program` is not sufficient.

#### The Best

- Initialize and return an OpenGL program object using the named vertex and fragment shader source files. On failure, print a message to `stderr` and return 0.

        GLuint init_program(const char *vert_filename,
                            const char *frag_filename)

#### The Rest

- Link and return a new program object with the given vertex and fragment shader objects. On failure, print a message to `stderr` and return 0.

        GLuint init_program(GLuint vert_shader,
                            GLuint frag_shader)

- Compile and return a new shader of the given type using the given GLSL source string. On failure, print a message to `stderr` and return 0.

        GLuint init_shader(GLenum type, const char *source)

- Load the named file into a newly-allocated, nul-terminated buffer. Return `NULL` on failure.

        char *read_shader_source(const char *filename)

- Check the shader compile status. On failure, print the log to `stream`. Return status.

        bool report_shader_status(GLuint shader, FILE *stream = stderr)

- Check the program link status. On failure, print the log to `stream`. Return status.

        bool report_program_status(GLuint program, FILE *stream = stderr)

