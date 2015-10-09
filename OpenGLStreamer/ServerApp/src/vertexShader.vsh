uniform mat4 qt_ModelViewProjectionMatrix;

attribute vec4 vertex;

void main(void)
{
	gl_Position = qt_ModelViewProjectionMatrix * vertex;
}

