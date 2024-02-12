#pragma once
#include <iostream>

using namespace std;

// structure for a node in the decision tree
struct node_t
{
	// constructor
	//constructor that takes in info string and sets info string
	node_t(const string& info) : info{ info } {}

	//make pure virual function so that it can be overriden
	virtual node_t* execute() = 0;

	string info;
	node_t* trueNode{ nullptr };	// pointer to true branch
	node_t* falseNode{ nullptr };	// pointer to false branch
};

// enum defining different types of predicates (Less, Greater, Equal, Not_Equal)
enum ePredicate
{
	Less,
	Greater,
	Equal,
	NotEqual
};

// function to convert enum predicate to string representation
inline string getString(ePredicate predicate)
{
	switch (predicate)
	{
	case ePredicate::Less:		return "<";
	case ePredicate::Greater:	return ">";
	case ePredicate::Equal:		return "==";
	case ePredicate::NotEqual:	return "!=";

	}

	return "";
}

template <typename T>
struct decision_t : public node_t
{
	// constructor
	decision_t(const string& info, T& parameter, ePredicate predicate, const T& value) :
		node_t{ info },
		parameter{ parameter },
		predicate{ predicate },
		value{ value }
	{}

	node_t* execute()
	{
		bool result = false;
		switch (predicate)
		{
			//case <set result based on predicate with parameter and value>
		case ePredicate::Less:
			result = parameter < value;
			break;
		case ePredicate::Greater:
			result = parameter > value;
		case ePredicate::Equal:
			result = parameter == value;
		case ePredicate::NotEqual:
			result = parameter != value;
		}

		cout << "descision: " << info << " : " << parameter << " " << getString(predicate) << " " << value << " (" << (result ? "true" : "false") << ")\n";

		// return true or false branch node based on result
		return result ? trueNode : falseNode;
	}

	T& parameter; // Reference to the parameter used for comparison
	T value; // Value for comparison
	ePredicate predicate; // Predicate used for comparison
};

struct action_t : public node_t
{
	// constructor
	//<constructor that takes in info string and calls parent class with info string>
	action_t(const string& info) : node_t{ info } {}

		virtual node_t* execute() override
	{
		cout << "action: " << info << endl;

		// action node is a leaf node (no children)
		//return a ptr to null
		return nullptr;
	}
};