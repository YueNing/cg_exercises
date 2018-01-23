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
// CG_REVISION e50df956fcfa03a7f7b84df5fdbc0718eb17ea54
