#ifdef GLEW_MX
GLboolean GLEWAPIENTRY glewContextIsSupported (const GLEWContext* ctx, const char* name)
#else
GLboolean GLEWAPIENTRY glewIsSupported (const char* name)
#endif
{
  const GLubyte* pos = (const GLubyte*)name;
  GLuint len = _glewStrLen(pos);
  GLboolean ret = GL_TRUE;
  while (ret && len > 0)
  {
    if (_glewStrSame1(&pos, &len, (const GLubyte*)"GL_", 3))
    {
// CG_REVISION 0b499c51037b55f8a55bc2b58f19cac16b11de4c
