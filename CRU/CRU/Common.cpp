//---------------------------------------------------------------------------
bool IsDigit(char Value)
{
	return Value >= '0' && Value <= '9';
}
//---------------------------------------------------------------------------
bool IsHexDigit(char Value)
{
	if (Value >= 'A' && Value <= 'F')
		return true;

	if (Value >= 'a' && Value <= 'f')
		return true;

	return IsDigit(Value);
}
//---------------------------------------------------------------------------
bool IsSpace(char Value)
{
	return Value == ' ';
}
//---------------------------------------------------------------------------
bool IsUpper(char Value)
{
	return Value >= 'A' && Value <= 'Z';
}
//---------------------------------------------------------------------------
bool IsLower(char Value)
{
	return Value >= 'a' && Value <= 'z';
}
//---------------------------------------------------------------------------
char ValueToHex(unsigned char Value)
{
	if (Value < 10)
		return Value + 48;

	return Value + 55;
}
//---------------------------------------------------------------------------
unsigned char HexToValue(char Value)
{
	if (IsDigit(Value))
		return Value - 48;

	return Value - 55;
}
//---------------------------------------------------------------------------
bool DataToHex(const unsigned char *Data, int Size, char *Text, bool Reverse)
{
	if (Reverse)
	{
		for (int Index = Size - 1; Index >= 0; Index--)
		{
			Text[0] = ValueToHex(Data[Index] >> 4);
			Text[1] = ValueToHex(Data[Index] & 15);
			Text += 2;
		}
	}
	else
	{
		for (int Index = 0; Index < Size; Index++)
		{
			Text[0] = ValueToHex(Data[Index] >> 4);
			Text[1] = ValueToHex(Data[Index] & 15);
			Text += 2;
		}
	}

	*Text = 0;
	return true;
}
//---------------------------------------------------------------------------
bool HexToData(const char *Text, unsigned char *Data, int Size, bool Reverse)
{
	while (IsSpace(*Text))
		Text++;

	if (Reverse)
	{
		for (int Index = Size - 1; Index >= 0; Index--)
		{
			if (!IsHexDigit(Text[0]) || !IsHexDigit(Text[1]))
				return false;

			if (Data)
			{
				Data[Index] = 0;
				Data[Index] |= HexToValue(Text[0]) << 4;
				Data[Index] |= HexToValue(Text[1]) & 15;
			}

			Text += 2;
		}
	}
	else
	{
		for (int Index = 0; Index < Size; Index++)
		{
			if (!IsHexDigit(Text[0]) || !IsHexDigit(Text[1]))
				return false;

			if (Data)
			{
				Data[Index] = 0;
				Data[Index] |= HexToValue(Text[0]) << 4;
				Data[Index] |= HexToValue(Text[1]) & 15;
			}

			Text += 2;
		}
	}

	while (IsSpace(*Text))
		Text++;

	if (*Text != 0)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool Trim(char *Text)
{
	char *Byte = Text;

	while (*Byte != 0)
		Byte++;

	Byte--;

	while (Byte >= Text && IsSpace(*Byte))
		Byte--;

	Byte++;
	*Byte = 0;
	Byte = Text;

	while (IsSpace(*Byte))
		Byte++;

	while (*Byte != 0)
	{
		*Text = *Byte;
		Text++;
		Byte++;
	}

	*Text = 0;
	return true;
}
//---------------------------------------------------------------------------
bool ToUpper(char *Text)
{
	while (*Text != 0)
	{
		if (IsLower(*Text))
			*Text -= 32;

		Text++;
	}

	return true;
}
//---------------------------------------------------------------------------
