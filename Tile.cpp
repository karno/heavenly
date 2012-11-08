// �ץ��饹�μ���

#include <vector>
#include <string>
#include <stdexcept>

#include "Tile.h"

using namespace std;

// ʸ�����ParseString��ǧ����ǽ�ʥȡ������ʬ�䤷�ޤ���
vector<string>* Tile::SplitTileArray(const string& str)
{
	// ����ѥ٥���
	vector<string>* ret = new vector<string>();
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= '1' && str[i] <= '9')
		{
			if (i + 1 == str.length())
			{
				// ���ͤǽ���äƤ��롢��������
				delete(ret);
				return 0;
			}
			else
			{
				// ���פΥ��ʥ饤��
				// m, p, s
				switch(str[i + 1])
				{
					case 'm':
					case 'p':
					case 's':
						ret->push_back(str.substr(i, 2));
						break;
					default:
						// ǧ���Ǥ��ʤ�
						delete(ret);
						return 0;
				}
			}
			// ��ʸ���ɤ���Τ�
			i++;
		}
		else
		{
			// ���פξ�ά��ˡ(e(T), s(N), w(S), n(P), p(W), g(H), r(C))
			switch(str[i])
			{
				case 'e':
				case 'T':
				case 's':
				case 'N':
				case 'w':
				case 'S':
				case 'n':
				case 'P':
				case 'p':
				case 'W':
				case 'g':
				case 'H':
				case 'r':
				case 'C':
					ret->push_back(str.substr(i, 1));
					break;
				default:
					delete(ret);
					return 0;
			}
		}
	}
	return ret;
}

// ʸ�������ץ��֥������ȥ��󥹥��󥹤�������ޤ���
// �����˼��Ԥ�����硢0(null)���֤�ޤ���
Tile* Tile::ParseString(const string& str)
{
	int len = str.length();
	if(len < 0 || len > 2)
		// invalid argument
		return 0;

	Tile *ret = new Tile();
	if(len == 1)
	{
		// ���פξ�ά��ˡ(e(T), s(N), w(S), n(P), p(W), g(H), r(C))
		switch(str[0])
		{
			case 'e':
			case 'T':
				ret->SetTypeValue(Honors, East);
				break;
			case 's':
			case 'N':
				ret->SetTypeValue(Honors, South);
				break;
			case 'w':
			case 'S':
				ret->SetTypeValue(Honors, West);
				break;
			case 'n':
			case 'P':
				ret->SetTypeValue(Honors, North);
				break;
			case 'p':
			case 'W':
				ret->SetTypeValue(Honors, White);
				break;
			case 'g':
			case 'H':
				ret->SetTypeValue(Honors, Green);
				break;
			case 'r':
			case 'C':
				ret->SetTypeValue(Honors, Red);
				break;
			default:
				// ǧ���Բ�
				delete(ret);
				return 0;
		}
	}
	else
	{
		if(str[0] >= '1' && str[0] <= '9')
		{
			switch(str[1])
			{
				case 'm':
					// �߻�
					ret->SetTypeValue(Characters, str[0] - '0');
					break;
				case 'p':
					// ����
					ret->SetTypeValue(Stones, str[0] - '0');
					break;
				case 's':
					// ����
					ret->SetTypeValue(Bamboos, str[0] - '0');
					break;
				default:
					delete(ret);
					return 0;
			}
		}
		else
		{
			// Invalid input
			delete(ret);
			return 0;
		}
	}
	return ret;
}

// ���󥹥ȥ饯��
Tile::Tile()
{
	this->gid = ++gidHolder;

}


// �׼���ͤ���ID�򥻥åȤ��ޤ���
int Tile::SetTypeValue(TileType type, int value)
{
	return this->id = (int)type * 10 + value;
}

// �׼��������ޤ���
Tile::TileType Tile::GetType() const
{
	switch(this->id / 10)
	{
		case 0:
			return Characters;
		case 1:
			return Stones;
		case 2:
			return Bamboos;
		case 3:
			return Honors;
		default:
			throw out_of_range("Type is invalid");
	}
}

// �פ��ͤ�������ޤ�����
// �׼郎���פξ�硢�ͤ�1-9����ޤ���
// �׼郎Honors�ξ�硢�ͤ�HonorValues����Τ��б����ޤ���
int Tile::GetValue() const
{
	return this->id % 10;
}

// �䥪���奦�פǤ��뤫Ƚ��
bool Tile::IsYaochu() const
{
	return (this->GetType() == Honors ||
		this->GetValue() == 1 ||
		this->GetValue() == 9);
}

// Ƚ�ɲ�ǽ��ʸ������֤��ޤ���(Ⱦ��2ʸ��ʬ)
string Tile::ToString() const
{
	string ret;
	switch(this->GetType())
	{
		case Honors:
			// ����
			switch(this->GetValue())
			{
				case East:
					return "��";
				case South:
					return "��";
				case West:
					return "��";
				case North:
					return "��";
				case White:
					return "��";
				case Green:
					return "�";
				case Red:
					return "��";
				default:
					throw range_error("honor value is invalid");
			}
			break;
		case Characters:
			// �߻�
			ret = "0m";
			break;
		case Stones:
			// ����
			ret = "0p";
			break;
		case Bamboos:
			// ����
			ret = "0s";
			break;
	}
	ret[0] += this->GetValue();
	return ret;
}

// �����Х�ID�����
int Tile::GetGid() const
{
	return this->gid;
}


// �����Х� ID
int Tile::gidHolder = 0;

