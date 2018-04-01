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
#include <unordered_map>

#include "spdlog/spdlog.h"

#include "Dsse/DataTypes.h"
#include "Dsse/Config.h"
#include "Dsse/SparseArray.h"
#include "Dsse/SparseArrayIterator.h"

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
    const static int NODECAP = 100;
    SparseArray<NodeBase*, NODECAP> m_nodes;
    std::unordered_map<String, NodeBase*> noderegistry;

	Dsse(std::shared_ptr<spdlog::logger> logger);
	Dsse();
	~Dsse();
	int Init();
	int Shutdown();
	void Update();

    int AddNode(String fullName, int parent=1, int nodeid=0);
	void DeleteNode(int nodeid);
	NodeBase* ReleaseNode(int nodeid); // does not destroy, up to caller!
	NodeBase* GetNode(int nodeid);

	//void MoveNode(int node, int container);
    bool ConnectInoutlets(int source, int outlet, int sink, int inlet);
    bool DisconnectInoutlets(int source, int outlet, int sink, int inlet);
    bool ClearInletConnections(int node, int inlet);
    bool ClearOutletConnections(int node, int outlet);

	void PrintNodes(std::ostream& stream, bool recursive=false);
	String PrintNodes(bool recursive=false);

    void RebuildUpdateSequence();

protected:
	String m_version = "0.1.0";
	std::shared_ptr<spdlog::logger> m_logger;
    std::list<int> updateSequence;

	int RegisterNode(NodeBase* node, int id); // known id (eg. from remote)
    bool CheckID(int id);
};

} // namespace dsse
#endif // ifndef DSSE_DSSE_H
