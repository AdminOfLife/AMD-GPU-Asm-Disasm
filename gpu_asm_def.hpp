#ifndef GPU_ASM_DEF_HPP
#define GPU_ASM_DEF_HPP
#include <string>
#include <vector>
#include <set>
#include <map>

namespace gpu_asm
{
	
struct bound
{
	int start;
	int stop;
};

struct enum_val
{
	std::string name;
	bound value_bound; //start == stop : simple enumeration; stop > start: name can have an offset
	
	bool operator == (const enum_val& b) const
	{
		return name == b.name;
	}
	
	bool operator > (const enum_val& b) const
	{
		return name > b.name;
	}
	
	bool operator < (const enum_val& b) const
	{
		return name < b.name;
	}
};

struct field
{
	std::string name;
	
	bound bits;
	
	//numeric constant
	bool numeric;
	bound numeric_bounds;
	
	//1bit flag
	bool flag;
	
	//enum
	std::set<enum_val> vals; 
	std::string enum_name;
};

struct microcode_format
{
	int size_in_bits;
	std::string name;
	std::vector<field> fields;
	std::map<std::string, std::set<enum_val> > enums;
};

struct microcode_format_tuple
{
	std::string name;
	int size_in_bits;
	std::vector<std::string> tuple;
	std::map<std::pair<std::string, std::string>, std::string> constraints; //KEY,VALUE pairs of field constraints in this format tuple
};

struct asm_definition
{
	std::string arch_techname; //R800
	std::string arch_codename; //Evergreen
	
	std::map<std::string, microcode_format> microcode_formats; //formats by name
	std::map<std::string, microcode_format_tuple> microcode_format_tuples;
	
	asm_definition(std::string text); //parse definitions from text
private:
	std::string clear_comments(std::string text);
};


}

#endif