#include "Sorting.h"

using namespace std;

static void Merge(vector<Unit>& units, int left, int mid, int right)
{
    vector<Unit> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (units[i].unitID <= units[j].unitID)
            temp.push_back(units[i++]);
        else
            temp.push_back(units[j++]);
    }

    while (i <= mid)
        temp.push_back(units[i++]);

    while (j <= right)
        temp.push_back(units[j++]);

    for (int k = 0; k < temp.size(); k++)
        units[left + k] = temp[k];
}

static void MergeSort(vector<Unit>& units, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    MergeSort(units, left, mid);
    MergeSort(units, mid + 1, right);

    Merge(units, left, mid, right);
}

void SortUnitsByID(vector<Unit>& units)
{
    if (!units.empty())
        MergeSort(units, 0, units.size() - 1);
}