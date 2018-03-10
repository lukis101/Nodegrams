 /*
	Copyright 2018 Lukas Jonyla

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#pragma once
#ifndef DSSE_DSSE_H
#define DSSE_DSSE_H

#include <ostream>
#include <vector>

#include "spdlog/spdlog.h"

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"

namespace dsse
{
class TypeRegistry;
class NodeBase;
class ContainerNode;

class DSSE_EXPORT Dsse
{
	//friend class NodeBase;
public:
    TypeRegistry* typereg;
    ContainerNode* rootcontainer;

	Dsse(std::shared_ptr<spdlog::logger> logger);
	Dsse();
	~Dsse();
	int Init();
	int Shutdown();
	void DoLogic(); // TEMPORARY

    int AddNode(NodeBase* node, int nodeid=0);
	void DeleteNode(int nodeid);
	NodeBase* ReleaseNode(int nodeid); // does not destroy, up to caller!

	NodeBase* GetNode(int nodeid);
	//void MoveNode(int nodeid, int destid);

	const std::vector<String> GetNodeList();
	const std::vector<NodeBase*> GetNodes();
	void PrintNodes(std::ostream stream, bool recursive=false);

protected:
	const static int NODECAP = 100;
	NodeBase* m_nodereg[NODECAP]; // !!! TODO
	int m_nodecount;
	int m_maxid; // highest registry index
	int m_minfreeid; // first(lowest) free index
	String m_version = "0.1.0";
	std::shared_ptr<spdlog::logger> m_logger;

	int RegisterNode(NodeBase* node, int id); // known id (eg. from remote)
private:
    bool CheckID(int id);
};

} // namespace dsse
#endif // ifndef DSSE_DSSE_H
