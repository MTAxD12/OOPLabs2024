﻿#pragma once

#include<iostream>
#include<algorithm>

class JsonValue {
public:
    virtual ~JsonValue() = 0;

    virtual void print(std::ostream& out, int level) const = 0;
};

void addIndentation(std::ostream& out, int level);


class NullValue : public JsonValue {
public:
    void print(std::ostream& out, int level) const override;
};

class NumberValue : public JsonValue {
    int nr;
public:
    NumberValue(int numar);
    void print(std::ostream& out, int level) const override;
};

class StringValue : public JsonValue {
    char* string;
public:
    StringValue(const char* s);
    void print(std::ostream& out, int level) const override;
};

class BoolValue : public JsonValue {
public:
    bool val;
    BoolValue(bool valoare);
    void print(std::ostream& out, int level) const override;
};

class ArrayValue : public JsonValue {
    JsonValue* elemente[16];
    unsigned int size;
public:
    void add(JsonValue* val);
    void print(std::ostream& out, int level) const override;
};

class ObjectValue : public JsonValue {
    std::pair<const char*, JsonValue*> perechi[16];
    unsigned int size;
public:
    void add(const char* nume, JsonValue* val);
    void print(std::ostream& out, int level) const override;
};

unsigned int nrNoduri(JsonValue* val);