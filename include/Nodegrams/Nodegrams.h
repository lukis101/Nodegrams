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
#ifndef NDGM_NODEGRAMS_H
#define NDGM_NODEGRAMS_H

#include <ostream>
#include <vector>
#include <unordered_map>

#include "spdlog/spdlog.h"

#include "Nodegrams/DataTypes.h"
#include "Nodegrams/Config.h"
#include "Nodegrams/SparseArray.h"
#include "Nodegrams/SparseArrayIterator.h"

namespace Nodegrams
{
class TypeRegistry;
class NodeBase;
class ContainerNode;

class NDGM_EXPORT Nodegrams
{
	//friend class NodeBase;

public:
    TypeRegistry* typereg;
    ContainerNode* rootcontainer;
    const static int NODECAP = 100;
    SparseArray<NodeBase*, NODECAP> m_nodes;
    std::unordered_map<String, NodeBase*> noderegistry;

	Nodegrams(std::shared_ptr<spdlog::logger> logger);
	Nodegrams();
	~Nodegrams();
	int Init();
	int Shutdown();
	void Update();

    bool RegisterNode(NodeBase*&& node);
    bool DeregisterNode(String fullname);
    int AddNode(String fullName, int parent=1, int nodeid=0);
	bool RemoveNode(int nodeid);
	//NodeBase* GetNode(int nodeid);

	//void MoveNode(int node, int container);
    bool ConnectInoutlets(int source, int outlet, int sink, int inlet);
    bool DisconnectInoutlets(int source, int outlet, int sink, int inlet);
    bool ClearInletConnections(int node, int inlet);
    bool ClearOutletConnections(int node, int outlet);

	void PrintNodes(std::ostream& stream, bool recursive=false);
	String PrintNodes(bool recursive=false);

    void RebuildUpdateSequence();

public:
	std::shared_ptr<spdlog::logger> m_logger;
protected:
	String m_version = "0.1.0";
    std::list<int> updateSequence;

	int RegisterNode(NodeBase* node, int id); // known id (eg. from remote)
    bool CheckID(int id);
};

} // namespace Nodegrams
#endif // ifndef NDGM_NODEGRAMS_H
