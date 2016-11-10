#pragma once

class IEquation : public COleDispatchDriver
{
public:
	IEquation() {}		// Calls COleDispatchDriver default constructor
	IEquation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IEquation(const IEquation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long Solve(VARIANT* z);
	double real(long i);
	double imag(long i);
	double diff(long i);
	long GetRootCount();
};
