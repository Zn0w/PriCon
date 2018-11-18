#pragma once

#include <string>

#define CODE_SIZE 16

enum Character
{
	a,		b,		c,		d,
	e,		f,		g,		h,
	i,		j,		k,		l,
	m,		n,		o,		p,
	q,		r,		s,		t,
	u,		v,		w,		x,
	y,		z
};

struct Symbol
{
	Character character;
	//const char* code;
	//std::string code;
	char code[CODE_SIZE];
};