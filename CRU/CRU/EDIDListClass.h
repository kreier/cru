//---------------------------------------------------------------------------
#ifndef EDIDListClassH
#define EDIDListClassH
//---------------------------------------------------------------------------
#define MAX_EDID_BLOCKS                 8
#define MAX_EDID_EXTENSION_BLOCKS       7
//---------------------------------------------------------------------------
class EDIDListClass
{
private:
	std::vector<unsigned char *> Items;
	int Count;

public:
	EDIDListClass();
	void Copy(const EDIDListClass &);
	void Delete();
	EDIDListClass(const EDIDListClass &);
	EDIDListClass &operator=(const EDIDListClass &);
	~EDIDListClass();
	bool Add(unsigned char *);
	bool Delete(int);
	int GetCount();
	bool MatchCompleteActive(unsigned char *);
	bool MatchCompleteOverride(unsigned char *, unsigned char *);
	bool MatchIncompleteOverride(unsigned char *, unsigned char *);
	bool MatchIncompleteActive(unsigned char *);
};
//---------------------------------------------------------------------------
#endif
