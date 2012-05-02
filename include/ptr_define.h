#ifndef MLPLUS_PTR_DEFINE_H
#define MLPLUS_PTR_DEFINE_H
#include <memory>
#include <tr1/memory>
#include "attribute.h"
#include "instance_interface.h"
#include "instance_container_interface.h"
#include "attribute_container_interface.h"
namespace mlplus
{
typedef std::tr1::shared_ptr<Attribute> SharedAttributePtr;
typedef std::tr1::shared_ptr<IInstance> SharedInstancePtr;
typedef std::tr1::shared_ptr<IAttributeContainer> SharedAttributeContainerPtr;
typedef std::tr1::shared_ptr<IInstanceContainer> SharedInstanceContainerPtr;
typedef std::auto_ptr<Attribute> AutoAttributePtr;
typedef std::auto_ptr<IInstance> AutoInstancePtr;
typedef std::auto_ptr<IAttributeContainer> AutoAttributeContainerPtr;
typedef std::auto_ptr<IInstanceContainer> AutodInstanceContainerPtr;
}
#endif
