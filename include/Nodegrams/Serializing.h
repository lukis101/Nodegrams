
#pragma once
#ifndef NDGM_SERIALIZING_H
#define NDGM_SERIALIZING_H

#include <stack>
#include <utility>

#include "Nodegrams/Config.h"
#include "Nodegrams/DataTypes.h"

#include "rapidjson/document.h"     // rapidjson's DOM-style API
/*#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"*/

namespace Nodegrams
{

class NDGM_EXPORT Serializer
{
	friend class Nodegrams;

public:
    Serializer(void) : doc(), ator(doc.GetAllocator())
    {
        valstack.push(&doc.SetObject());
    }
    ~Serializer() { assert(keystack.size() == 0); assert(valstack.size() == 1); }

    void SetKey(String keyname)
    {
        curKey = keyname;
    }

    void StartObject()
    {
        rapidjson::Value* obj = new rapidjson::Value(rapidjson::kObjectType);
        valstack.push(obj);
        keystack.push(curKey);
    }
    void EndObject()
    {
        String key = keystack.top();
        keystack.pop();
        rapidjson::Value* obj = valstack.top();
        valstack.pop();
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(*obj, ator);
        else
            valstack.top()->AddMember(rapidjson::Value(key, ator).Move(), *obj, ator);
        delete obj;
    }

    void StartArray()
    {
        rapidjson::Value* arr = new rapidjson::Value(rapidjson::kArrayType);
        valstack.push(arr);
        keystack.push(curKey);
    }
    void EndArray()
    {
        String key = keystack.top();
        keystack.pop();
        rapidjson::Value* arr = valstack.top();
        valstack.pop();
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(*arr, ator);
        else
        {
            assert(valstack.top()->IsObject());
            valstack.top()->AddMember(rapidjson::Value(key, ator).Move(), *arr, ator);
        }
        delete arr;
    }

    void AddNull()
    {
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(rapidjson::Value().Move(), ator);
        else
            valstack.top()->AddMember(rapidjson::Value(curKey, ator).Move(), rapidjson::Value().Move(), ator);
    }

    void AddBool(bool value)
    {
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(rapidjson::Value(value).Move(), ator);
        else
            valstack.top()->AddMember(rapidjson::Value(curKey, ator).Move(), value, ator);
    }

    void AddString(String value)
    {
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(rapidjson::Value(value, ator).Move(), ator);
        else
            valstack.top()->AddMember(rapidjson::Value(curKey, ator).Move(), value, ator);
    }

    void AddInt(int value)
    {
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(rapidjson::Value(value).Move(), ator);
        else
            valstack.top()->AddMember(rapidjson::Value(curKey, ator).Move(), value, ator);
    }
    void AddUint(unsigned int value)
    {
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(rapidjson::Value(value).Move(), ator);
        else
            valstack.top()->AddMember(rapidjson::Value(curKey, ator).Move(), value, ator);
    }

    void AddDouble(double value)
    {
        if (valstack.top()->IsArray())
            valstack.top()->PushBack(rapidjson::Value(value).Move(), ator);
        else
            valstack.top()->AddMember(rapidjson::Value(curKey, ator).Move(), value, ator);
    }

private:
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& ator;
    String curKey;
    std::stack<String> keystack;
    std::stack<rapidjson::Value*> valstack;
};

} // namespace Nodegrams
#endif // ifndef NDGM_SERIALIZING_H
