
#ifndef __ges_marshal_MARSHAL_H__
#define __ges_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:OBJECT (gesmarshal.list:1) */
#define ges_marshal_VOID__OBJECT	g_cclosure_marshal_VOID__OBJECT

/* VOID:OBJECT,INT,INT (gesmarshal.list:2) */
extern void ges_marshal_VOID__OBJECT_INT_INT (GClosure     *closure,
                                              GValue       *return_value,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint,
                                              gpointer      marshal_data);

G_END_DECLS

#endif /* __ges_marshal_MARSHAL_H__ */

