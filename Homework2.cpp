#include <iostream>
using namespace std;

int main()
{
	int select = 4;
		if (select == 0) {
			int len;

			cout << "Enter a number: ";
			cin >> len;

			for (int i = 0; i < len; i++)
			{
				for (int j = i + 1; j < len; j++)
				{
					cout << " ";
				}
				cout << "#" << endl;
			}
		}
		else if (select == 1) {
			int len;

			cout << "Enter a number: ";
			cin >> len;

			for (int i = 0; i < len; i++)
			{
				int j = i + 1;
				while (j < len)
				{
					cout << " ";
					j++;
				}
				cout << "#" << endl;

			}
		}
		else if (select == 2) {
			int len;

			cout << "Enter a number: ";
			cin >> len;

			int i = 0;
			do {
				if (len > 0) {
					int j = i + 1;
					while (j < len)
					{
						cout << " ";
						j++;
					}
					cout << "#" << endl;

					i++;
				}
			} while (i < len);

		}
		else if (select == 3) {
		int month;
		cout << "Enter a month: ";
		cin >> month;

			if (month == 6)
				cout << "summer solstice";
			else if (month == 12)
				cout << "winter solstice";
			else if (month == 3 || month == 9)
				cout << "equinox";
			else
				cout << "nothing special";

		}
		else if (select == 4) {
			int month;
			cout << "Enter a month: ";
			cin >> month;

			switch (month)
			{
			case 6:
				cout << "summer solstice";
				break;
			case 12:
				cout << "winter solstice";
				break;
			case 3:
			case 9:
				cout << "equinox";
				break;
			default:
				cout << "nothing special";
			}

		}
}