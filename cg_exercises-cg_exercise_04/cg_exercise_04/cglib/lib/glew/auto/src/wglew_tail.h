/* ------------------------------------------------------------------------- */

#ifdef GLEW_MX

typedef struct WGLEWContextStruct WGLEWContext;
GLEWAPI GLenum GLEWAPIENTRY wglewContextInit (WGLEWContext *ctx);
GLEWAPI GLboolean GLEWAPIENTRY wglewContextIsSupported (const WGLEWContext *ctx, const char *name);

#define wglewInit() wglewContextInit(wglewGetContext())
#define wglewIsSupported(x) wglewContextIsSupported(wglewGetContext(), x)

#define WGLEW_GET_VAR(x) (*(const GLboolean*)&(wglewGetContext()->x))
#define WGLEW_GET_FUN(x) wglewGetContext()->x

#else /* GLEW_MX */

GLEWAPI GLenum GLEWAPIENTRY wglewInit ();
GLEWAPI GLboolean GLEWAPIENTRY wglewIsSupported (const char *name);

#define WGLEW_GET_VAR(x) (*(const GLboolean*)&x)
#define WGLEW_GET_FUN(x) x

#endif /* GLEW_MX */

GLEWAPI GLboolean GLEWAPIENTRY wglewGetExtension (const char *name);

#ifdef __cplusplus
}
#endif

#undef GLEWAPI

#endif /* __wglew_h__ */
// CG_REVISION e50df956fcfa03a7f7b84df5fdbc0718eb17ea54
