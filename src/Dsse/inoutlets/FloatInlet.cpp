
//#include <iostream>

#include "spdlog/spdlog.h"

#include "Dsse/inoutlets/InletBase.h"
#include "Dsse/inoutlets/FloatInlet.h"
#include "Dsse/inoutlets/FloatOutlet.h"
#include "Dsse/nodes/NodeBase.h"

//#include "Dsse/DataTypes.h"
//#include "Dsse/DssEngine.h"

namespace dsse
{
	
FloatInlet::FloatInlet(NodeBase* node, String name, String desc, float defValue)
	: InletBase(node, name, desc)
{
	m_defValue = defValue;
	m_inValue = m_defValue;
	
	spdlog::get("iolet")->info("Float \"{}\" constr()", GetFullName());
}
FloatInlet::~FloatInlet()
{
	spdlog::get("iolet")->info("Float \"{}\" destr()", GetFullName());
}

bool FloatInlet::Connect(FloatOutlet* outlet)
{
	if( IsConnected() /*&& PARAMS["InletOverrideConnection"] == false*/ ) // TODO
	{
		spdlog::get("iolet")->error("{} Already connected!", GetFullName());
		return false;
	}
	m_connection = static_cast<OutletBase*>(outlet);
	return true;
}
void FloatInlet::ReceiveData(float data)
{
	if( m_inValue != data )
	{
		m_inValue = data;
		m_dataChanged = true;
	}
	m_dataReady = true;
}
String FloatInlet::GetDataString()
{
	return "TODO";
}

} // namespace dsse