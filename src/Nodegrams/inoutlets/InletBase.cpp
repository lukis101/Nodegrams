
#include "spdlog/spdlog.h"

#include "Nodegrams/inoutlets/InletBase.h"
#include "Nodegrams/nodes/NodeBase.h"

namespace Nodegrams {
namespace Nodes
{

InletBase::InletBase(NodeBase* node, Data::DataBox* data, String name, String desc)
    : DataHolder(data)
{
	m_node = node;
	this->name = name;
	this->description = desc;

	spdlog::get("iolet")->debug("InletBase \"{}\" constr()", GetFullName());
}
InletBase::~InletBase()
{
	spdlog::get("iolet")->debug("InletBase \"{}\" destr()", GetFullName());
}

String InletBase::GetFullName()
{
	String fname;
	fname.reserve(m_node->name.size() + 4 + name.size());
	fname += m_node->name;
	fname += ":in:";
	fname += name;
	return fname;
}

}
} // namespace Nodegrams
