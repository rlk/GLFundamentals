# GLFundamentals

GLFundamentals is C++ header that provides the basic functionality necessary to make effective use of modern OpenGL (e.g. OpenGL 3.2 Core Profile or OpenGL ES 2.0 or later).

Given the lack of fixed functionality and matrix handling, all applications will need to load and compile shaders and perform matrix arithmetic. Thus, these capabilities are provided here.

All of the following symbols are defined in the `gl` namespace.

## Types

### 3-vector

`struct vec3` represents a 3-component vector of `GLfloat` values.

- Constructor initializing to (0, 0, 0).

        vec3()

- Constructor initializing to (x, y, z).

        vec3(GLfloat x, GLfloat y, GLfloat z)

- Accessors giving array-like subscripting.

        const GLfloat& operator[](int i) const
              GLfloat& operator[](int i)

### 4-vector

`struct vec4` represents a 4-component vector of `GLfloat` values.

- Constructor initializing to (0, 0, 0, 0).

        vec4()

- Constructor initializing to (x, y, z, w).

        vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)

- Array-like subscript accessors returning scalar values.

        const GLfloat& operator[](int i) const
              GLfloat& operator[](int i)

### 3-matrix

`struct mat3` represents a 3x3 matrix of `GLfloat` values.

- Constructor initializing to the identity.

        mat3()

- Constructor with full initialization.

        mat3(GLfloat m00, GLfloat m01, GLfloat m02,
             GLfloat m10, GLfloat m11, GLfloat m12,
             GLfloat m20, GLfloat m21, GLfloat m22)

- Array-like subscript accessors returning vec3 row vectors.

        const vec3& operator[](int i) const
              vec3& operator[](int i)

- Cast-to-float giving row-order matrix data.

            operator const GLfloat*() const

### 4-matrix

`struct mat4` represents a 4x4 matrix of `GLfloat` values.

- Constructor initializing to the identity.

        mat4()

- Constructor with full initialization.

        mat4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
             GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
             GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
             GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33)

- Array-like subscript accessors returning vec4 row vectors.

        const vec3& operator[](int i) const
              vec3& operator[](int i)

- Cast-to-float giving row-order matrix data.

            operator const GLfloat*() const


## Vector-matrix Functions

- Convert an angle in degrees to an angle in radians.

        GLfloat to_radians(GLfloat degrees)

- Convent an angle in radians to an angle in degrees.

        GLfloat to_degrees(GLfloat radians)

- Calculate the 3-component sum of `v` and `w`.

        vec3 operator+(const vec3& v, const vec3& w)

- Calculate the 3-component difference of `v` and `w`.

        vec3 operator-(const vec3& v, const vec3& w)

- Calculate the 3-component scalar quotient of `v` and `k`.

        vec3 operator/(const vec3& v, GLfloat k)

- Calculate the 3-component scalar product of `v` and `k`.

        vec3 operator*(const vec3& v, GLfloat k)

- Calculate the 3-component dot product of `v` and `w`.

        GLfloat operator*(const vec3& v, const vec3& w)

- Calculate the 4-component dot product of `v` and `w`.

        GLfloat operator*(const vec4& v, const vec4& w)

- Calculate the 3-component transform of vector `v` by matrix `A`.

        vec3 operator*(const mat3& A, const vec3& v)

- Calculate the 4-component transform of vector `v` by matrix `A`.

        vec4 operator*(const mat4& A, const vec4& v)

- Calculate the 3x3 matrix product of `A` and `B`.

        mat3 operator*(const mat3& A, const mat3& B)

- Calculate the 4x4 matrix product of `A` and `B`.

        mat4 operator*(const mat4& A, const mat4& B)

- Compute the length of vector `v`.

        GLfloat length(const vec3 &v)

- Compute the cross product of vectors `v` and `w`.

        vec3 cross(const vec3& v, const vec3& w)

- Compute the normalization of vector `v`.

        vec3 normalize(const vec3& v)

- Return a matrix giving a rotation about X through `a` radians.

        mat4 xrotation(GLfloat a)

- Return a matrix giving a rotation about Y through `a` radians.

        mat4 yrotation(GLfloat a)

- Return a matrix giving a rotation about Z through `a` radians.

        mat4 zrotation(GLfloat a)

- Return a matrix giving a translation along vector `v`.

        mat4 translation(const vec3& v)

- Return a matrix giving a scale along vector `v`.

        mat4 scale(const vec3& v)

- Return a matrix giving a perspective projection with field-of-view `v`, aspect ratio `a`, near clipping distance `n`, and far clipping distance `f`.

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

## Shader Functions

- Load the named file into a newly-allocated buffer. Append nul.

        char *read_shader_source(const char *name)

- Check the shader compile status. If failed, print the log. Return status.

        bool report_shader_status(GLuint shader, FILE *fp = stderr)

- Check the program link status. If failed, print the log. Return status.

        bool report_program_status(GLuint program, FILE *fp = stderr)

- Compile and return a new shader of the given type using the given GLSL source string. Return 0 on failure.

        GLuint init_shader(GLenum type, const char *source)

- Link and return a new program object with the given vertex and fragment shader objects. Return 0 on failure.

        GLuint init_program(GLuint vert_shader,
                            GLuint frag_shader)

- Initialize and return an OpenGL program object using the named vertex and fragment shader source files. Return 0 on failure.

        GLuint init_program(const char *vert_name,
                            const char *frag_name)

