/*
 * ===========================================================================
 *
 *       Filename:  Variable.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wed Jan 26 2022
 *       Revision:
 *       Compiler:
 *
 *         Author:  Joe Kanoza
 *   Organization:  ${ORG}
 *
 * ===========================================================================
 */

#pragma once

class Variable
{
private:
	/* data */
public:
	std::string name;
	double value;
	Variable(/* args */);
	Variable(std::string s, double val) :name{s}, value{val} {};
	~Variable();
};

Variable::Variable(/* args */)
{
}

Variable::~Variable()
{
}

vector<Variable> var_table{};

double get_value(string s)
{
	for(const Variable& v: var_table)
		if(v.name == s) return v.value;

	error("get:undefined variable ", s);
}

void set_value(string s, double d)
{
	for(Variable& v:var_table)
	{
		if(v.name == s)
		{
			v.value = d;
			return;
		}
	}
	error("set: undifined variable ",s);
}

bool is_declared(string var)
// is var already in var_table?
{
	for(const Variable& v: var_table)
		if(v.name == var)return true;
	return false;
}

double define_name(string var, double val)
// add {var,val} to var_table
{
	if(is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable{var,val});
	return val;
}