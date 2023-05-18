#include "Units.h"

BaseUnit::BaseUnit()
{
    this->_name = "";
    this->_code = "";
}

BaseUnit::~BaseUnit()
{
}

BaseUnit::BaseUnit(std::string name, std::string code)
{
    this->_code = code;
    this->_name = name;
}

std::string BaseUnit::name()
{
    return this->_name;
}

std::string BaseUnit::code()
{
    return this->_code;
}

bool BaseUnit::operator<(const BaseUnit& B)
{
    return this->_code < B._code;
}

bool BaseUnit::operator==(const BaseUnit& B)
{
    return this->_code == B._code;
}

bool BaseUnit::operator>(const BaseUnit& B)
{
    return this->_code > B._code;
}

bool BaseUnit::operator!=(const BaseUnit& B)
{
    return this->_code != B._code;
}

void BaseUnit::printAllInfo()
{
    std::cout << "BaseUnit{ name: " << this->_name << ", code: " << this->_code << " }";
}

BaseUnitNode::BaseUnitNode()
{
    this->pre = nullptr;
    this->trans_factor_pre = 0;
}

BaseUnitNode::~BaseUnitNode()
{
    delete this->pre;
    this->pre = nullptr;
    for (int i = 0; i < this->next.size(); i++) {
        delete this->next[i];
        this->next[i] = nullptr;
    }
    this->next.clear();
    this->trans_factor_next.clear();
}

void BaseUnitNode::add_nextNode(BaseUnitNode& node)
{
    std::lower_bound(this->next.begin(),this->next.end(),node)
}
