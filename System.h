#ifndef __C_SYSTEM__
#define __C_SYSTEM__

#include <vector>
#include <cstdio>

using namespace std;

class System
{

	public:

		template <typename T>
			static vector<T> CloneVector(const vector<T>& vec)
			{
				vector<T> clone;
				for (typename vector<T>::const_iterator iter = vec.begin();
						iter != vec.end();
						++iter)
				{
					clone.push_back(*iter);
				}
				return clone;
			}

		template <typename T>
			static vector<vector<T> > CloneVecVec(const vector<vector<T> >& vec)
			{
				vector<vector<T> > clone;
				for (typename vector<vector<T> >::const_iterator iter = vec.begin();
						iter != vec.end();
						++iter)
				{
					clone.push_back(CloneVector(*iter));
				}
				return clone;
			}

		inline static void WaitInput()
		{
			fflush(stdin);
			getchar();
		}
};

#endif

