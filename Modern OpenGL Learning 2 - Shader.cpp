vector<GLuint> shaderList;
const string vertexShader(
	"#version 330\n"
	"layout(location = 0) in vec4 position;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = position;\n"
	"}\n"
);


GLuint CreateShader(GLenum shaderType, const string& shaderFile);
GLuint CreateProgram(vector<GLuint>& shaderList);

void init()
{
	GLuint shader = CreateShader(GL_VERTEX_SHADER, vertexShader);

	shaderList.push_back(shader);

	Gluint program = CreateProgram(shaderList);

	glUseProgram(program);

	...

	glUseProgram(0);
}

GLuint CreateShader(GLenum shaderType, const string& shaderFile)
{
	GLuint shader = glCreateShader(shaderType);
	const char* shaderFileData = shaderFile.c_str();
	glShaderSource(shader, 1, &shaderFileData, NULL);
	glCompileShader(shader);


	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);

		cerr << infoLog << endl;
		delete[] infoLog;
	}

	return shader;
}

GLuint CreateProgram(vector<GLuint>& shaderList)
{
	GLuint program = glCreateProgram();

	for (int i = 0; i < shaderList.size(); i++)
	{
		glAttachShader(program, shaderList[i]);
	}

	glLinkProgram(program);

	GLuint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);

		cerr << infoLog << endl;
		delete[] infoLog;
	}

	for(int i = 0; i < shaderList.size(); i++)
	{
		glDetachShader(program, shaderList[i]);
	}

	return program;
}