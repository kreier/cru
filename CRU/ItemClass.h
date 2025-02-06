//---------------------------------------------------------------------------
#ifndef ItemClassH
#define ItemClassH
//---------------------------------------------------------------------------
class ItemClass
{
public:
	virtual bool Read(const unsigned char *, int) = 0;
	virtual bool Write(unsigned char *, int) = 0;
};
//---------------------------------------------------------------------------
#endif
