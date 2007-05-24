
#ifndef __cc_marshal_MARSHAL_H__
#define __cc_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* BOOLEAN:OBJECT,BOXED (marshallers.list:1) */
extern void cc_marshal_BOOLEAN__OBJECT_BOXED (GClosure     *closure,
                                              GValue       *return_value,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint,
                                              gpointer      marshal_data);

/* BOOLEAN:OBJECT,ENUM (marshallers.list:2) */
extern void cc_marshal_BOOLEAN__OBJECT_ENUM (GClosure     *closure,
                                             GValue       *return_value,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint,
                                             gpointer      marshal_data);

/* VOID:BOXED,BOXED (marshallers.list:3) */
extern void cc_marshal_VOID__BOXED_BOXED (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);

/* VOID:INT,OBJECT (marshallers.list:4) */
extern void cc_marshal_VOID__INT_OBJECT (GClosure     *closure,
                                         GValue       *return_value,
                                         guint         n_param_values,
                                         const GValue *param_values,
                                         gpointer      invocation_hint,
                                         gpointer      marshal_data);

/* VOID:OBJECT,BOXED (marshallers.list:5) */
extern void cc_marshal_VOID__OBJECT_BOXED (GClosure     *closure,
                                           GValue       *return_value,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint,
                                           gpointer      marshal_data);

G_END_DECLS

#endif /* __cc_marshal_MARSHAL_H__ */

