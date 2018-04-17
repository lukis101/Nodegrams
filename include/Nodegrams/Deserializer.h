
#pragma once
#ifndef NDGM_DESERIALIZER_H
#define NDGM_DESERIALIZER_H

#include <stack>
#include <utility>

#include "Nodegrams/Config.h"
#include "Nodegrams/DataTypes.h"

#include "rapidjson/document.h"

namespace Nodegrams
{

class NDGM_EXPORT Deserializer
{
	friend class Nodegrams;

public:
    Deserializer(rapidjson::Value& rootobj)
    {
        assert(rootobj.IsObject());
        valstack.push(&rootobj);
    }
    ~Deserializer() { assert(valstack.size() == 1); }

    bool KeyExists(String keyname)
    {
        return valstack.top()->HasMember(keyname);
    }

    bool SelectMember(String keyname)
    {
        rapidjson::Value* pval = valstack.top();
        assert(pval->IsObject());
        rapidjson::Value::MemberIterator itr = pval->FindMember(keyname);
        if (itr == pval->MemberEnd())
            return false;
        valstack.push(&(itr->value));
        return true;
    }
    bool SelectIndex(unsigned index)
    {
        rapidjson::Value* pval = valstack.top();
        assert(pval->IsArray());
        if (!pval->IsArray())
            return false;
        if (index > pval->Size())
            return false;
        valstack.push(&((*pval)[index]));
        return true;
    }
    void Pop()
    {
        assert(valstack.size() > 1);
        valstack.pop();
    }

    unsigned ArraySize()
    {
        rapidjson::Value* pval = valstack.top();
        if (!pval->IsArray())
            return 0;
        return pval->Size();
    }

    String GetString()
    {
        rapidjson::Value* pval = valstack.top();
        if (!pval->IsString())
            return "";
        return pval->GetString();
    }

    double GetDouble()
    {
        rapidjson::Value* pval = valstack.top();
        if (!pval->IsDouble())
            return 0;
        return pval->GetDouble();
    }

    int GetInt()
    {
        rapidjson::Value* pval = valstack.top();
        if (!pval->IsInt())
            return 0;
        return pval->GetInt();
    }
    unsigned int GetUint()
    {
        rapidjson::Value* pval = valstack.top();
        if (!pval->IsUint())
            return 0;
        return pval->GetUint();
    }

private:
    rapidjson::Document doc;
    //String curKey;
    std::stack<rapidjson::Value*> valstack;
};

} // namespace Nodegrams
#endif // ifndef NDGM_DESERIALIZER_H
