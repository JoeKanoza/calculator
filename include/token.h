/*
 * ===========================================================================
 *
 *       Filename:  token.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Fri Dec 24 2021
 *       Revision:
 *       Compiler:
 *
 *         Author:  Joe Kanoza
 *   Organization:  ${ORG}
 *
 * ===========================================================================
 */

#pragma once

double primary();
double term();
double expression();
void calculate();
void clean_up_mess();

const char name = 'a';			// name token
const char let = 'L';			// declaration token
const char sqrt_char = 'S';
const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";	// declaration keyword
const string sqrtkey = "sqrt";


// user-defined type to handle tokens
class Token {
	public:
		char kind; 	//what kind of token
		double value;	//for numbers: a value
		string name;
		Token(): kind{0}{}
		Token(char k) :kind{k}, value{0.0} {}	// construct from one value
		Token(char k, double v) :kind{k}, value{v} {}	// construct from two values
		Token(char k, string n) :kind{k}, name{n} {} 	// initialize kind and name
};
