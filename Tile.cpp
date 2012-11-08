// 牌クラスの実装

#include <vector>
#include <string>
#include <stdexcept>

#include "Tile.h"

using namespace std;

// 文字列をParseStringで認識可能なトークンに分割します。
vector<string>* Tile::SplitTileArray(const string& str)
{
	// 戻り用ベクタ
	vector<string>* ret = new vector<string>();
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= '1' && str[i] <= '9')
		{
			if (i + 1 == str.length())
			{
				// 数値で終わっている、おかしい
				delete(ret);
				return 0;
			}
			else
			{
				// 数牌のアナライズ
				// m, p, s
				switch(str[i + 1])
				{
					case 'm':
					case 'p':
					case 's':
						ret->push_back(str.substr(i, 2));
						break;
					default:
						// 認識できない
						delete(ret);
						return 0;
				}
			}
			// 二文字読んだので
			i++;
		}
		else
		{
			// 字牌の省略記法(e(T), s(N), w(S), n(P), p(W), g(H), r(C))
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

// 文字から牌オブジェクトインスタンスを取得します。
// 生成に失敗した場合、0(null)が返ります。
Tile* Tile::ParseString(const string& str)
{
	int len = str.length();
	if(len < 0 || len > 2)
		// invalid argument
		return 0;

	Tile *ret = new Tile();
	if(len == 1)
	{
		// 字牌の省略記法(e(T), s(N), w(S), n(P), p(W), g(H), r(C))
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
				// 認識不可
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
					// 萬子
					ret->SetTypeValue(Characters, str[0] - '0');
					break;
				case 'p':
					// 筒子
					ret->SetTypeValue(Stones, str[0] - '0');
					break;
				case 's':
					// 索子
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

// コンストラクタ
Tile::Tile()
{
	this->gid = ++gidHolder;

}


// 牌種と値からIDをセットします。
int Tile::SetTypeValue(TileType type, int value)
{
	return this->id = (int)type * 10 + value;
}

// 牌種を取得します。
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

// 牌の値を取得します。　
// 牌種が数牌の場合、値は1-9を取ります。
// 牌種がHonorsの場合、値はHonorValues列挙体に対応します。
int Tile::GetValue() const
{
	return this->id % 10;
}

// ヤオチュウ牌であるか判定
bool Tile::IsYaochu() const
{
	return (this->GetType() == Honors ||
		this->GetValue() == 1 ||
		this->GetValue() == 9);
}

// 判読可能な文字列を返します。(半角2文字分)
string Tile::ToString() const
{
	string ret;
	switch(this->GetType())
	{
		case Honors:
			// 字牌
			switch(this->GetValue())
			{
				case East:
					return "東";
				case South:
					return "南";
				case West:
					return "西";
				case North:
					return "北";
				case White:
					return "白";
				case Green:
					return "發";
				case Red:
					return "中";
				default:
					throw range_error("honor value is invalid");
			}
			break;
		case Characters:
			// 萬子
			ret = "0m";
			break;
		case Stones:
			// 筒子
			ret = "0p";
			break;
		case Bamboos:
			// 索子
			ret = "0s";
			break;
	}
	ret[0] += this->GetValue();
	return ret;
}

// グローバルIDを取得
int Tile::GetGid() const
{
	return this->gid;
}


// グローバル ID
int Tile::gidHolder = 0;

