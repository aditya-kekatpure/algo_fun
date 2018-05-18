#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <bitset>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>

#include "trie.h"

using namespace std;

void merge(vector<int>& arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// create 2 arrays
	int* L = new int[n1];
	int* R = new int[n2];
	
	for (int i = 0; i < n1; ++i)
	{
		L[i] = arr[l - i];
	}

	for (int j = 0; j < n2; ++j)
	{
		R[j] = arr[j + m + 1];
	}

	i = 0, j = 0, k = 0;

	while (l < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k++] = L[i++];
		}
		else
		{
			arr[k++] = R[j++];
		}
	}

	while (l < n1)
	{
		arr[k++] = L[i++];
	}

	while (r < n2)
	{
		arr[k++] = R[j++];
	}
}

void mergeSortRecurse(vector<int>& arr, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;

		mergeSortRecurse(arr, l, m);
		mergeSortRecurse(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void mergeSort(vector<int>& arr)
{
	mergeSortRecurse(arr, 0, arr.size() - 1);
}

// two sum
vector<int> twoSum(vector<int>& nums, int target)
{
	unordered_map<int, int> unorderedMap;	

	for (int i = 0; i != nums.size(); i++)
	{
		int complement = target - nums[i];
		std::unordered_map<int, int>::const_iterator hm1_Iter;
		
		hm1_Iter = unorderedMap.find(complement);

		if (hm1_Iter != unorderedMap.end())
		{
			return vector<int> {i, hm1_Iter->second };
		}

		unorderedMap[nums[i]] = i;
	}

	return vector<int>();
}

vector<vector<int>> threeSum1(vector<int>& nums, int target)
{
	vector<vector<int>> result;

	if (nums.size() <= 2)
	{
		return result;
	}

	sort(nums.begin(), nums.end());

	for (int x = 0; x < nums.size();)
	{
		int start = x + 1; 
		int end = nums.size() - 1;

		while (start < end)
		{
			if (nums[x] + nums[start] + nums[end] == target)
			{
				result.push_back(vector<int> {nums[x], nums[start], nums[end]});
				start++, end--;
				
				while ((start < end) && nums[start] == nums[start - 1])
				{
					start++;
				}

				while ((start < end) && nums[end] == nums[end + 1])
				{
					end--;
				}
			}
			else if (nums[x] + nums[start] + nums[end] < target)
			{
				start++;

				while ((start < end) && nums[start] == nums[start - 1])
				{
					start++;
				}
			}
			else
			{
				end--;
				
				while ((start < end) && nums[end] == nums[end + 1])
				{
					end--;
				}
			}
		}
		x++;
		while ((x < nums.size()) && nums[x] == nums[x - 1])
		{
			x++;
		}
	}
	return result;
}

vector<vector<int> > threeSum(vector<int>& nums) {
	if (nums.size() <= 2) return {};
	vector<vector<int> > rtn;
	sort(nums.begin(), nums.end());

	for (int i = 0; i < nums.size();) {
		int start = i + 1, end = nums.size() - 1;

		while (start < end) {
			if (nums[i] + nums[start] + nums[end] == 0) {
				rtn.push_back({ nums[i],nums[start],nums[end] });
				start++;
				end--;
				while ((start < end) && nums[start] == nums[start - 1]) start++;
				while ((start < end) && nums[end] == nums[end + 1]) end--;

			}
			else if (nums[i] + nums[start] + nums[end]<0) {
				start++;
				while ((start < end) && nums[start] == nums[start - 1]) start++;
			}
			else {
				end--;
				while ((start < end) && nums[end] == nums[end + 1]) end--;
			}
		}

		i++;
		while ((i < nums.size()) && nums[i] == nums[i - 1])
			i++;

	}
	return rtn;
}

vector<vector<int>> threeSumZero(vector<int>& nums)
{
	// triplets whose sum equals zero

	vector<vector<int>> result;
	int n = nums.size();
	for (int i = 0; i < n-1; ++i)
	{
		unordered_set<int> set;

		for (int j = i + 1; j < n; ++j)
		{
			int complement = -1 * (nums[i] + nums[j]);
			
			if (set.find(complement) != set.end())
			{
				result.push_back(vector<int> {complement, nums[i], nums[j]});
			}
			else
			{
				set.insert(nums[j]);
			}
		}
	}

	return result;
}

int reverse(int x)
{
	long ans = 0;

	while (x)
	{
		ans = ans * 10 + x % 10;
		x = x / 10;

		if (ans > INT32_MAX || ans < INT32_MIN)
		{
			return 0;
		}
	}
	return (int)ans;
}

bool isPalindrome(int x)
{
	// find the divisor to extract the leading digit
	int divisor = 1;
	while (x / divisor >= 10)
	{
		divisor *= 10;
	}

	while (x != 0)
	{
		int start = x / divisor; // 2332 / 1000 = 2
		int end = x % 10; // 2332 % 10 = 2

		if (start != end)
		{
			return false;
		}

		// move places and remove first and last digits
		x = (x % divisor) / 10; // 2332 % 1000 / 10 = 332 / 10 = 33
		divisor = divisor / 100; // reduce divisor by factor of 100 - since 2 digits are removed.
	}

	return true;
}

bool isPalindromeLogn(int x)
{
	// if x != 0 or x is negative
	if (x < 0 || (x % 10 == 0 && x != 0))
	{
		return false;
	}

	int reverted = 0;
	while (reverted < x)
	{
		reverted = reverted * 10 + x % 10; // 0, 2332 => 2, 2332 => 23, 233
		x /= 10; // => 2, 233 => 23, 23
	}

	// get rid of the middle digit if present
	return x == reverted || x == reverted / 10;
}

int romanToInt(string roman)
{
	if (roman.empty())
	{
		return 0;
	}

	std::unordered_map<char, int> mp = { { 'I', 1 }, { 'V', 5 }, { 'X', 10 },{ 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };

	int sum = mp[roman.back()];
	for (int i = roman.size() - 2; i >= 0; i--)
	{
		sum += mp[roman[i]] >= mp[roman[i + 1]] ? mp[roman[i]] : -mp[roman[i]];
	}

	return sum;
}

bool isParanthesisValid(string s)
{
	int count = 0;
	unordered_map<char, char> complements = { { '{', '}' }, { '[', ']' }, { '(', ')' } };

	string fin = "";

	if (s.size() < 2)
	{
		return false;
	}

	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '{' || s[i] == '[' || s[i] == '(')
		{
			count++;
			fin += complements[s[i]];
		}

		else 
		{
			if (fin.size() == 0)
			{
				return false;
			}
			if (s[i] == fin.back())
			{
				count--;
				fin = fin.substr(0, fin.size() - 1);
			}
			else
			{
				return false;
			}
		}
	}

	return count == 0;
}

#pragma region trie test

void buildTrie(trie* root, vector<string>& strs)
{
	for (auto s : strs)
	{
		root->insertRecursive(s);
	}
}

#pragma endregion


#pragma region LinkedList_Definition

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

void push(ListNode** headRef, int data)
{
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->val = data;
	newNode->next = (*headRef);
	(*headRef) = newNode;
}

ListNode* insert(int* ints, int length)
{
	ListNode* head = NULL;
	ListNode** headRef = &head;

	for (int i = 0; i < length; ++i)
	{
		push(headRef, ints[i]);
		headRef = &((*headRef)->next);
	}

	return head;
}

// build linked list

// merge 2 sorted linked lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
	ListNode dummy(0);
	ListNode* tail = &dummy;

	while (l1 && l2)
	{
		if (l1->val < l2->val)
		{
			tail->next = l1;
			l1 = l1->next;
		}
		else
		{
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;
	}

	tail->next = l1 ? l1 : l2;
	return dummy.next;
}

ListNode* deleteDuplicates(ListNode* head)
{
	if (!head)
	{
		return head;
	}

	ListNode* current = head;
	while (current->next != NULL)
	{
		if (current->val == current->next->val)
		{
			current->next = current->next->next;
		}
		else
		{
			current = current->next;
		}
	}

	return head;
}

#pragma endregion

// remove duplicates from sorted array
//int removeDuplicates(vector<int>& nums)
//{
//	int* p1 = &nums[0];
//	int* p2 = &nums[1];
//
//	std::vector<int>::iterator it = nums.begin();
//	while (p2 != &nums[nums.size()-1])
//	{
//		if (&p1 == &p2)
//		{
//			p2++;
//		}
//		else if (&p1 < &p2)
//		{
//
//
//			p1++;
//			p2++;
//		}
//
//	}
//}

// remove duplicates
int removeDuplicates(vector<int>& nums)
{
	if (nums.empty())
	{
		return 0;
	}

	int i = 0;
	for (int j = 1; j < nums.size();j++)
	{
		if (nums[i] != nums[j])
		{
			i++;
			nums[i] = nums[j];
		}
	}

	return i+1;
}

int removeDuplicatesv2(vector<int>& nums)
{
	int count = 0;
	for (int i = 1; i < nums.size(); ++i)
	{
		if (nums[i] == nums[i - 1])
		{
			count++;
		}
		else
		{
			nums[i - count] = nums[i];
		}
	}

	return nums.size() - count;
}

int removeDuplicatesv3(vector<int>& nums)
{
	int i = !nums.empty();

	for (int n : nums)
	{
		if (n > nums[i - 1])
		{
			nums[i++] = n;
		}
	}
	return i;
}

// remove element from int array
int removeElement(vector<int>& nums, int val)
{
	int k = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] != val)
		{
			nums[k] = nums[i];
			k++;
		}
	}
	return k;
}

// remove element from int array, does not preserve sorted order.
int removeElementv2(vector<int>& nums, int val)
{
	int i = 0;
	int k = nums.size();

	while (i < k)
	{
		if (nums[i] == val)
		{
			nums[i] = nums[k-1];
			k--;
		}
		else
		{
			i++;
		}
	}

	return k;
}

void mergeTwoSortedArrays(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	/* algo - 
	1. start populating nums1 from back
	2. iterate only for nums2 since nums1 is already in sorted order.
	*/

	int i = m - 1;
	int j = n - 1;
	int k = m + n - 1;

	while (j >= 0)
	{
		nums1[k--] = i >= 0 && nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
	}
}

int strStr(string haystack, string needle)
{
	int index = -1;
	int i = 0, j = 0;

	if (needle.length() == 0)
	{
		return 0;
	}

	while (j < haystack.length())
	{
		if (needle[i] == haystack[j])
		{
			index = j;
			while (i < needle.length())
			{
				if (needle[i++] != haystack[j++])
				{
					j = index + 1, index = -1, i = 0;
					break;
				}
			}
		}
		else
		{
			j++;
		}
	}

	return index;
}

int binarySearch(vector<int> &nums, int start, int end, int target)
{
	if (start <= end)
	{
		int pivot = start + (end - start) / 2;

		if (nums[pivot] == target)
		{
			return pivot;
		} 
		if (nums[pivot] > target)
		{
			return binarySearch(nums, start, pivot-1, target);
		}
		else
		{
			return binarySearch(nums, pivot + 1, end, target);
		}
	}

	return -1;
}

int binarySearchNumber(vector<int> &nums, int target)
{
	// implement binary search
	if (nums.size() == 0)
	{
		return -1;
	}

	int start = 0, end = nums.size() - 1, pivot;

	while (start <= end)
	{
		pivot = start + (end - start) / 2;

		if (nums[pivot] < target)
		{
			start = pivot + 1;
		}
		else
		{
			end = pivot - 1;
		}
	}

	return start;
}

bool isBadVersion(int version)
{
	if (version >= 9)
	{
		return true;
	}
	return false;
}

int firstBadVersion(int n)
{
	int start = 0, end = n - 1, pivot;

	while (start <= end)
	{
		pivot = start + (end - start) / 2;

		if (!isBadVersion(pivot))
		{
			start = pivot + 1;
		}
		else
		{
			end = pivot - 1;
		}
	}

	return start;
}

string countAndSay(int n)
{
	if (n == 1)
	{
		return "1";
	}

	if (n == 2)
	{
		return "11";
	}

	string say = "11";
	for (int i = 3; i <= n; ++i)
	{
		say += '$';
		int cnt = 1;
		string temp = "";

		for (int j = 1; j < say.length(); ++j)
		{
			if (say[j] != say[j - 1])
			{
				temp += cnt + '0';
				temp += say[j - 1];
				cnt = 1;
			}
			else
			{
				cnt++;
			}
		}
		say = temp;
	}
	return say;
}
#pragma region dynamic_programming

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int min(int a, int b)
{
	return (a > b) ? b : a;
}

int max(int a, int b, int c)
{
	return max(max(a, b), c);
}

int maxCrossingSum(vector<int> &arr, int s, int m, int e)
{
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = 0; i <= m; ++i)
	{
		sum += arr[i];
		if (left_sum < sum)
		{
			left_sum = sum;
		}
	}

	sum = 0;
	int right_sum = INT_MIN;
	for (int j = m + 1; j <= e; ++j)
	{
		sum += arr[j];
		if (right_sum < sum)
		{
			right_sum = sum;
		}
	}

	return left_sum + right_sum;
}

int maxSubArraySum(vector<int> &arr, int s, int e)
{
	if (s == e)
	{
		return arr[s];
	}

	int m = (s + e) / 2;

	return max(maxSubArraySum(arr, s, m), maxSubArraySum(arr, m + 1, e), maxCrossingSum(arr, s, m, e));
}

int maxSubArraySum_KadaneAlgorithm(vector<int>& a)
{
	int max_so_far = INT_MIN;
	int max_ending_here = 0;

	for (int i = 0; i < a.size(); ++i)
	{
		max_ending_here += a[i];
		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
		}

		if (max_ending_here < 0)
		{
			max_ending_here = 0;
		}
	}

	return max_so_far;
}

int climbingStairs(int n) // dynamic programming
{
	if (n == 1)
	{
		return 1;
	}

	if (n == 2)
	{
		return 2;
	}

	vector<int> dp(n+1);
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; ++i)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}

	return dp[n];
}

int climbingStairsNoDP(int n)
{
	if (n == 1)
	{
		return 1;
	}

	int first = 1;
	int second = 2;
	for (int i = 3; i <= n; ++i)
	{
		int third = first + second;
		first = second;
		second = third;
	}

	return second;
}

#pragma endregion

int lengthOfLastWord(string s)
{
	int cnt = 0, end = s.length() - 1;

	while (end >= 0 && s[end] == ' ')
	{
		end--;
	}
	
	for (int i = end; i >= 0; i--)
	{
		if (s[i] != ' ')
		{
			cnt++;
		}
		else
		{
			break;
		}
	}

	return cnt;
}

/*
suppose you have a number in your list/array such that adding 1 would make it a two digit number,
eg: [9]
o/p: [1,0]
Plusone(9) would be [10], but the expected output should be [1,0] such that the most significant digit is on the head
*/
vector<int> plusOne(vector<int>& digits)
{
	int n = digits.size();
	for (auto i = n - 1; i >= 0; --i)
	{
		if (digits[i] == 9)
		{
			digits[i] = 0;
		}
		else
		{
			digits[i]++;
			return digits;
		}
	}

	digits[0] = 1;
	digits.push_back(0);

	return digits;
}

int sqrt(int n)
{
	int x = (int)pow(n, 0.5);
	return x;
}

int sqrtNewton(int x)
{
	long r = x;
	while (r*r > x)
	{
		r = (r + x / r) / 2;
	}

	return r;
}

#pragma region tree

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode* next;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* newTreeNode(int data)
{
	return new TreeNode(data);
}

TreeNode* insertTree(TreeNode* root, int data)
{
	if (root == NULL)
	{
		root = newTreeNode(data);
		return root;
	}
	if (data < root->val)
	{
		root->left = insertTree(root->left, data);
	}
	else
	{
		root->right = insertTree(root->right, data);
	}

	return &(*root);
}

TreeNode* insertTreeInverse(TreeNode* root, int data)
{
	if (root == NULL)
	{
		root = newTreeNode(data);
		return root;
	}
	if (data > root->val)
	{
		root->left = insertTree(root->left, data);
	}
	else
	{
		root->right = insertTree(root->right, data);
	}

	return &(*root);
}

void insertTree(TreeNode** root, int data)
{
	if (*root == NULL)
	{
		*root = newTreeNode(data);
		return;
	}

	if (data < (*root)->val)
	{
		insertTree(&(*root)->left, data);
	}
	else
	{
		insertTree(&(*root)->right, data);
	}
}

bool isSameTree(TreeNode* p, TreeNode* q)
{
	if ((p == NULL) || (q == NULL))
	{
		return p == q;
	}

	// base case
	if (p->val != q->val)
	{
		return false;
	}

	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

bool isMirrorTree(TreeNode* p, TreeNode* q)
{
	if ((p == NULL) || (q == NULL))
	{
		return p == q;
	}

	// base case
	if (p->val != q->val)
	{
		return false;
	}

	return isMirrorTree(p->left, q->right) && isMirrorTree(p->right, q->left);
}

bool isSymmetricTree(TreeNode* left, TreeNode* right)
{
	if ((left == NULL) || (right == NULL))
	{
		return left == right;
	}

	// base case
	if (left->val != right->val)
	{
		return false;
	}

	return isSymmetricTree(left->left, right->right) && isSymmetricTree(left->right, right->left);
}

bool isSymmetric(TreeNode* root)
{
	if (!root)
	{
		return true;
	}

	return isSymmetricTree(root->left, root->right);
}

int maxTreeDepth(TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	return 1 + max(maxTreeDepth(root->left), maxTreeDepth(root->right));
}

void levelOrder(vector<vector<int>> &ans, TreeNode* root, int level)
{
	if (!root)
	{
		return;
	}

	//if (level >= ans.size())
	//{
	//	ans.push_back({});
	//}
	
	ans[level].push_back(root->val);
	levelOrder(ans, root->left, level - 1);
	levelOrder(ans, root->right, level - 1);
}

vector<vector<int>> levelOrderBottom(TreeNode* root)
{
	int depth = ::maxTreeDepth(root);
	vector<vector<int>> ans(depth, vector<int> {});
	levelOrder(ans, root, depth-1);
	// reverse(ans.begin(), ans.end));
	return ans;
}

TreeNode* sortedArrayToBSTHelper(vector<int> nums, int start, int end)
{
	int pivot = start + (end - start) / 2;
	TreeNode* node = new TreeNode(nums[pivot]);

	if (start == end)
	{
		return node;
	}

	if (start <= pivot - 1)
	{
		node->left = sortedArrayToBSTHelper(nums, start, pivot - 1);
	}

	if (pivot + 1 <= end)
	{
		node->right = sortedArrayToBSTHelper(nums, pivot + 1, end);
	}

	return node;
}

TreeNode* sortedArrayToBST(vector<int>& nums)
{
	if (nums.size() == 0)
	{
		return NULL;
	}

	return sortedArrayToBSTHelper(nums, 0, nums.size() - 1);
}

#pragma endregion

int digitToValue(char c)
{
	return c - '0';
}

int convertFromBase(string number, int base)
{
	if (base < 2 || (base > 10 && base != 16))
	{
		return -1;
	}

	int value = 0;
	for (int i = number.length()-1; i >= 0; --i)
	{
		int digit = digitToValue(number[i]);
		if (digit < 0 || digit >= base)
		{
			return -1;
		}

		int exp = number.length() - 1 - i;
		value += digit * pow(base, exp);
	}

	return value;
}

bool compareBinHex(string binary, string hex)
{
	int n1 = convertFromBase(binary, 2);
	int n2 = convertFromBase(hex, 16);
	if (n1 < 0 || n2 < 0)
	{
		return false;
	}

	return n1 == n2;
}

ListNode* addTwoNumber(ListNode* l1, ListNode* l2)
{
	if (l1 == NULL)
	{
		return l2;
	}

	if (l2 == NULL)
	{
		return l1;
	}

	ListNode* c1 = l1;
	ListNode* c2 = l2;

	ListNode* result = new ListNode(0);
	ListNode* cr = result;
	int sum = 0;

	while (c1 != NULL || c2 != NULL)
	{
		sum /= 10;
		if (c1 != NULL)
		{
			sum += c1->val;
			c1 = c1->next;
		}

		if (c2 != NULL)
		{
			sum += c2->val;
			c2 = c2->next;
		}

		cr->next = new ListNode(sum % 10);
		cr = cr->next;
	}

	if (sum / 10 == 1)
	{
		cr->next = new ListNode(1);
	}

	return result->next;
}

ListNode* returnNthFromEnd(ListNode* head, int n)
{
	ListNode* first = head;
	ListNode* second = head;

	for (int i = 0; i < n; ++i)
	{
		second = second->next;
	}

	while (second->next != NULL)
	{
		first = first->next;
		second = second->next;
	}
	return first;
}

ListNode* removeNthFromEnd(ListNode* head, int n)
{
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* first = dummy;
	ListNode* second = dummy;

	for (int i = 0; i <= n; ++i)
	{
		second = second->next;
	}

	while (second != NULL)
	{
		first = first->next;
		second = second->next;
	}

	first->next = first->next->next;

	return dummy->next;
}

int lengthOfLongestSubstring(string s)
{
	unordered_map<char, int> charMap;
	int start = -1;
	int maxLen = 0;

	for (int i = 0; i < s.size(); ++i)
	{
		if (charMap.count(s[i]) != 0) // count number of times 'char' appears in the unordered_map.
		{
			start = max(start, charMap[s[i]]);
		}
		charMap[s[i]] = i; // store the latest index of the char. if duplicates, store the latest one.
		maxLen = max(maxLen, i - start);
	}

	return maxLen;
}

int maxAreaContainer(vector<int>& height)
{
	// the trick to use here is to use array indexes as width and their corresponding values as height

	int maxArea = 0, start = 0, end = height.size() - 1;

	while (start < end)
	{
		maxArea = max(maxArea, min(height[start], height[end]) * (end - start));
		height[start] < height[end] ? start++ : end--;
	}

	return maxArea;
}

vector<string> letterCombinations(string digits)
{
	string map[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	vector<string> result;

	if (digits.empty())
	{
		return vector<string>();
	}

	result.push_back("");
	for (int i = 0; i < digits.size(); ++i)
	{
		int num = digits[i] - '0';
		if (num == 1 || num == 0)
		{
			continue;
		}

		const string& perm = map[num];
		vector<string> temp;
		for (int j = 0; j < perm.size(); ++j)
		{
			for (int k = 0; k < result.size(); ++k)
			{
				temp.push_back(result[k] + perm[j]);
			}
		}
		result.swap(temp);
	}
	return result;
}

void wellFormedParenthesisHelper(vector<string>& result, string currentStr, int open, int close, int n)
{
	if (currentStr.length() == 2 * n)
	{
		result.push_back(currentStr);
		return;
	}
	
	if (open < n)
	{
		wellFormedParenthesisHelper(result, currentStr + "(", open + 1, close, n);
	}
	if (open > close)
	{
		wellFormedParenthesisHelper(result, currentStr + ")", open, close + 1, n);		
	}
}

vector<string> wellFormedParenthesis(int n)
{
	vector<string> v;

	if (n > 0)
	{
		wellFormedParenthesisHelper(v, "", 0, 0, n);
	}
	return v;
}

int mydivide(int dividend, int divisor)
{
	if (divisor == 0 || divisor == -1)
	{
		return INT_MAX;
	}

	bool negative = (dividend < 0) ^ (divisor < 0);
	dividend = abs(dividend);
	divisor = abs(divisor);
	int count = 0;
	
	int subRes = dividend;
	while (subRes >= divisor)
	{
		subRes -= divisor;
		count++;
	}

	return negative ? -count : count;
}

int divide_Complicated(int dividend, int divisor)
{
	long long result = 0;
	long long m = abs((long long)dividend);
	long long n = abs((long long)divisor);

	while (m >= n)
	{
		long long s = n, power = 1;
		while ((s << 1) <= m)
		{
			s <<= 1;
			power <<= 1;
		}
		result += power;
		m -= s;
	}

	if ((dividend > 0) ^ (divisor > 0))
	{
		result = -result;
	}
	return result > INT_MAX ? INT_MAX : result;
}

int divide(int dividend, int divisor)
{
	if (!divisor || (dividend == INT_MIN && divisor == -1))
	{
		return INT_MAX;
	}

	bool neg = (dividend > 0) ^ (divisor > 0);
	long long divdend = labs(dividend);
	long long divsor = labs(divisor);
	int result = 0;

	while (divdend >= divsor)
	{
		long long temp = divsor, count = 1;
		while (divdend >= (temp << 1))
		{
			temp <<= 1;
			count <<= 1;
		}

		divdend -= temp;
		result += count;
		
	}

	return neg ? -result : result;
}

int searchInRotatedArray(vector<int>& nums, int target)
{
	int lo = 0, hi = nums.size() - 1;

	while (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		if ((nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid]))
		{
			lo = mid + 1;
		}
		else
		{
			hi = mid;
		}
	}
	
	return lo = hi && nums[lo] == target ? lo : -1;
}

int searchInternal(vector<int>& nums, int lo, int hi, int target)
{
	if (lo > hi)
	{
		return -1;
	}

	int mid = lo + (hi - lo) / 2;

	if (nums[mid] == target)
	{
		return mid;
	}

	// if nums[lo..mid] is sorted
	if (nums[lo] <= nums[mid])
	{
		// since array is sorted, its either in the left half or the right
		if (target >= nums[lo] && target <= nums[mid])
		{
			return searchInternal(nums, lo, mid - 1, target);
		}

		return searchInternal(nums, mid + 1, hi, target);
	}

	// if nums[mid..hi] is sorted
	if (target >= nums[mid] && target <= nums[hi])
	{
		return searchInternal(nums, mid + 1, hi, target);
	}

	return searchInternal(nums, lo, mid - 1, target);
}

int search(vector<int>& nums, int target)
{
	int l = 0, h = nums.size() - 1;

	return searchInternal(nums, l, h, target);
}

vector<int> searchRange(vector<int>& nums, int target)
{
	int start = -1, end = nums.size() - 1;

	for (int i = 0; i <= end; ++i)
	{
		if (nums[i] == target)
		{
			start = i;
			break;
		}
	}

	if (start == -1)
	{
		return vector<int> {-1, -1};
	}

	for (int j = end; j >= start; --j)
	{
		if (nums[j] == target)
		{
			end = j;
			break;
		}
	}

	return vector<int> { start, end };
}

int searchRangeBinaryHelper(vector<int>& nums, int target, bool left)
{
	int lo = 0, hi = nums.size() - 1;

	while (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;

		if (nums[mid] > target || (left && target == nums[mid]))
		{
			hi = mid;
		}
		else
		{
			lo = mid + 1;
		}
	}

	return lo;
}

vector<int> searchRangeBinary(vector<int>& nums, int target)
{
	vector<int> targetRange = { -1, -1 };

	int l = searchRangeBinaryHelper(nums, target, true);

	if (l == nums.size() || (nums[l] != target))
	{
		return targetRange;
	}

	targetRange[0] = l;
	targetRange[1] = searchRangeBinaryHelper(nums, target, false);

	return targetRange;
}

bool validSudoku(vector<vector<char>>& board)
{
	bool row[9][9] = { false };
	bool col[9][9] = { false };
	bool box[9][9] = { false };

	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board[i].size(); ++j)
		{
			if (board[i][j] != '.')
			{
				int num = board[i][j] - '1';

				if (row[i][num]++)
				{
					return false;
				}

				if (col[j][num]++)
				{
					return false;
				}

				if (box[i / 3][j / 3]++)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool validSudokuAccepted(vector<vector<char>>& board)
{
	bool used1[9][9] = { false }, used2[9][9] = { false }, used3[9][9] = { false };

	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board[i].size(); ++j)
		{
			if (board[i][j] != '.')
			{
				int num = board[i][j] - '0' - 1, k = i / 3 * 3 + j / 3;
				if (used1[i][num] || used2[j][num] || used3[k][num])
				{
					return false;
				}
				used1[i][num] = used2[j][num] = used3[k][num] = true;
			}
		}
	}
	return true;
}

void permuteRecursion(vector<int>& nums, int index, vector<vector<int>>& result)
{
	if (index >= nums.size())
	{
		result.push_back(nums);
		return;
	}

	for (int i = index; i < nums.size(); ++i)
	{
		swap(nums[index], nums[i]);
		permuteRecursion(nums, index + 1, result);
		
		// reset
		swap(nums[index], nums[i]);
	}
}

vector<vector<int>> permute(vector<int>& nums)
{
	vector<vector<int>> result;

	permuteRecursion(nums, 0, result);
	return result;
}

void rotate(vector<vector<int>>& matrix)
{
	// transpose of the matrix - a(i,j) => a(j,i)
	// clockwise -> swap columns
	// anticlockwise -> swap rows

	int rows = matrix.size();
	int cols = matrix[0].size();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}

	for (int i = 0; i < rows; ++i)
	{
		int j = 0, k = matrix[i].size() - 1;
		while (j < k)
		{
			std::swap(matrix[i][j], matrix[i][k]);
			j++, k--;
		}
	}
}

vector<vector<string>> groupAnagramsOwn(vector<string>& strs)
{
	int len = strs.size();
	vector<vector<string>> results;
	unordered_map<int, vector<string>> anagrams;
	unordered_map<int, vector<string>>::iterator iter;

	for (int i = 0; i < len; ++i)
	{
		int charValue = 0;
		for (int j = 0; j < strs[i].length(); ++j)
		{
			charValue ^= strs[i][j];
		}

		if (anagrams.find(charValue) != anagrams.end())
		{
			anagrams[charValue].push_back(strs[i]);
		}
		else
		{
			anagrams.insert({ charValue, vector<string> {strs[i]} });
		}
	}

	iter = anagrams.begin();
	while (iter != anagrams.end())
	{
		results.push_back(iter->second);
		iter++;
	}

	return results;
}

string strSort(string& str)
{
	int count[26] = { 0 };
	int n = str.length();

	for (int i = 0; i < n; ++i)
	{
		count[str[i] - 'a']++;
	}

	int index = 0;
	string temp(n, 'a');
	for (int j = 0; j < 26; ++j)
	{
		for (int k = 0; k < count[j]; ++k)
		{
			temp[index++] += j;
		}
	}

	return temp;
}

vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
	unordered_map<string, vector<string>> map;
	for (string s : strs)
	{
		string temp = strSort(s);
		map[temp].push_back(s);
	}

	vector<vector<string>> anagrams;
	for (auto m : map)
	{
		anagrams.push_back(m.second);
	}

	return anagrams;
}

double myPow(double base, int n)
{
	if (n == 0)
	{
		return 1;
	}
	double temp = myPow(base, n / 2);

	if (n % 2 != 0)
	{
		return (n < 0) ? 1 / base*temp*temp : base * temp*temp;
	}
	else
	{
		return temp * temp;
	}
}

vector<int> spiralOrder(vector<vector<int>> &m)
{
	int r1 = 0, r2 = m.size() - 1;
	int c1 = 0, c2 = m[0].size() - 1;
	vector<int> result;

	while (r1 <= r2 && c1 <= c2)
	{
		for (int c = c1; c <= c2; ++c)
		{
			result.push_back(m[r1][c]);
		}
		for (int r = r1 + 1; r < r2; ++r)
		{
			result.push_back(m[r][c2]);
		}

		if (r1 < r2 && c1 < c2)
		{
			for (int c = c2 - 1; c > c1; --c)
			{
				result.push_back(m[r2][c]);
			}
			for (int r = r2; r > r1; --r)
			{
				result.push_back(m[r][c1]);
			}
		}

		r1++;
		r2--;
		c1++;
		c2--;
	}

	return result;
}

bool canJump(vector<int>& nums)
{
	int n = nums.size();
	int lastPos = n - 1;

	for (int i = n - 1; i >= 0; --i)
	{
		if (i + nums[i] >= lastPos)
		{
			lastPos = i;
		}
	}

	return lastPos == 0;
}

struct Interval
{
	int start;
	int end;

	Interval() : start(0), end(0)
	{
	}

	Interval(int s, int e) : start(s), end(e)
	{
	}
};

vector<Interval> mergeIntervals(vector<Interval>& ins)
{
	if (ins.empty())
	{
		return vector<Interval> {};
	}
	vector<Interval> res;

	sort(ins.begin(), ins.end(), [](Interval a, Interval b)
	{
		return a.start < b.start;
	});

	res.push_back(ins[0]);
	for (int i = 1; i < ins.size(); ++i)
	{
		if (res.back().end < ins[i].start)
		{
			res.push_back(ins[i]);
		}
		else
		{
			res.back().end = max(res.back().end, ins[i].end);
		}
	}
	return res;
}

int uniquePathsRecursive(int n, int m)
{
	if (n == 1 || m == 1)
	{
		return 1;
	}

	return uniquePathsRecursive(n - 1, m) + uniquePathsRecursive(n, m - 1);

	/*
	 The problem with the above approach is that it is too slow. Run time is exponential, 2^n
	 */
}

int uniquePaths(int n, int m)
{
	// lets try dynamic programming solution, dp

	vector<vector<int>> count(n, vector<int>(m));

	for (int i = 0; i < n; ++i)
	{
		count[i][0] = 1;
	}

	for (int j = 0; j < m; ++j)
	{
		count[0][j] = 1;
	}

	for (int k = 1; k < n; ++k)
	{
		for (int l = 1; l < m; ++l)
		{
			count[k][l] = count[k - 1][l] + count[k][l - 1];
		}
	}

	return count[n - 1][m - 1];
}

void setZeroes(vector<vector<int>> mat)
{
	if (mat.size() == 0)
	{
		return;
	}

	int r = mat.size();
	int c = mat[0].size();

	bool firstRow = false;
	bool firstCol = false;

	// set first row = 0, if required
	for (int i = 0; i < c; ++i)
	{
		if (mat[0][i] == 0)
		{
			firstRow = true;
		}
	}

	// set first column = 0, if required
	for (int j = 0; j < r; ++j)
	{
		if (mat[j][0] == 0)
		{
			firstCol = true;
		}
	}

	// mark columns and rows that need to be set to zero
	for (int k = 1; k < r; ++k)
	{
		for (int l = 1; l < c; ++l)
		{
			if (mat[k][l] == 0)
			{
				mat[k][0] = 0;
				mat[0][l] = 0;
			}
		}
	}

	// now mark the columns and rows as zero
	for (int p = 1; p < r; ++p)
	{
		for (int q = 1; q < c; ++q)
		{
			if (mat[0][q] == 0 || mat[p][0] == 0)
			{
				mat[p][q] = 0;
			}
		}
	}

	// now mark the first Row and first column to zero if required.
	if (firstRow)
	{
		for (int v = 0; v < c; ++v)
		{
			mat[0][v] = 0;
		}
	}

	if (firstCol)
	{
		for (int w = 0; w < r; ++w)
		{
			mat[w][0] = 0;
		}
	}
}

void sortColorsTLE(vector<int>& nums)
{
	if (nums.size() == 0)
	{
		return;
	}

	int i = 0, j = 0, k = nums.size() - 1;

	while (j <= k)
	{
		if (nums[j] == 0)
		{
			nums[j] = nums[i];
			nums[i] = 0;
			i++; j++;
		}

		if (nums[j] == 1)
		{
			j++;
		}

		if (nums[k] == 2)
		{
			nums[j] = nums[k];
			nums[k] = 2;
			j++;
			k--;
		}
	}
}

void sortColors(vector<int>& nums)
{
	int r = 0, w = 0, b = 0;
	for (int n : nums)  // 1,2,0,0,1,1,2,0
	{
		(nums[b++] = 2) && n < 2 && (nums[w++] = 1) && n < 1 && (nums[r++] = 0);
	}
}

void backtrackSubset(vector<vector<int>>& res, vector<int>& temp, vector<int>& nums, int start)
{
	res.push_back(temp);

	for (int i = start; i < nums.size(); ++i)
	{
		temp.push_back(nums[i]);
		backtrackSubset(res, temp, nums, i + 1);
		temp.pop_back();
	}
}

vector<vector<int>> subsets(vector<int>& nums)
{
	if (nums.size() == 0)
	{
		return vector<vector<int>>();
	}

	vector<vector<int>> result;
	sort(nums.begin(), nums.end());
	vector<int> temp;

	backtrackSubset(result, temp, nums, 0);
	return result;
}

bool isValidChar(char c)
{
	return c != '0';
}

bool isValidChar(char x, char y)
{
	return (x == '1') || (x == '2' && y <= '6');
}

int numDecodingsBuggy(string s)
{
	int n = s.size();

	if (n == 0 || s[0] == '0')
	{
		return 0;
	}

	if (n == 1)
	{
		return 1;
	}

	int m1 = 1, m2 = 1, num;
	for (int i = 1; i < n; ++i)
	{
		if (!isValidChar(s[i]) || !isValidChar(s[i-1], s[i]))
		{
			return 0;
		}

		if (isValidChar(s[i]))
		{
			num = m1;
		}

		if (isValidChar(s[i-1], s[i]))
		{
			num += m2;
		}
		m2 = m1;
		m1 = num;
	}
	return num;
}

int numDecodings(string s)
{
	int n = s.size();
	if (!n || s[0] == '0')
	{
		return 0;
	}

	int f0 = 1, f1 = 1, f2, i;
	for (i = 2; i <= n; ++i)
	{
		f2 = (int)(s[i - 1] != '0')*f1 + (int)((s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] < '7'))*f0;
		f0 = f1;
		f1 = f2;
	}

	return f1;
}

vector<int> inorderTraversal(TreeNode* root)
{
	if (root == NULL)
	{
		return vector<int> {};
	}

	vector<int> result;
	stack<TreeNode*> stak;
	TreeNode* curr = root;

	while (curr != NULL || !stak.empty())
	{
		if (curr)
		{
			stak.push(curr);
			curr = curr->left;
		}
		else
		{
			TreeNode* temp = stak.top();
			result.push_back(temp->val);
			stak.pop();
			curr = temp->right;
		}
	}
	return result;
}

bool isValidBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode)
{
	if (!root)
	{
		return true;
	}

	if (minNode && root->val <= minNode->val || maxNode && root->val >= maxNode->val)
	{
		return false;
	}

	return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
}

bool isValidBST(TreeNode* root)
{
	return isValidBST(root, NULL, NULL);
}

vector<vector<int>> levelOrder(TreeNode* root)
{
	vector<vector<int>> result;
	queue<TreeNode*> q;

	if (root)
	{
		q.push(root);
	}
	while (!q.empty())
	{
		int len = q.size();
		vector<int> level;

		for (int i = 1; i < len; ++i)
		{
			TreeNode* node = q.front();
			level.push_back(node->val);

			if (node->left)
			{
				q.push(node->left);
			}

			if (node->right)
			{
				q.push(node->right);
			}

			q.pop();
		}
		result.push_back(level);
	}

	return result;
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
	vector<vector<int>> result;

	if (!root)
	{
		return result;
	}

	deque<TreeNode*> deq;
	deq.push_back(root);
	bool isZig = true;

	while (!deq.empty())
	{
		int len = deq.size();
		isZig = !isZig;
		vector<int> level;

		while (len--)
		{
			if (isZig)
			{
				root = deq.front();
				deq.pop_front();
				level.push_back(root->val);
				if (root->right)
				{
					deq.push_back(root->right);
				}
				if (root->left)
				{
					deq.push_back(root->left);
				}
			}
			else
			{
				root = deq.back();
				deq.pop_back();
				level.push_back(root->val);
				if (root->left)
				{
					deq.push_front(root->left);
				}
				if (root->right)
				{
					deq.push_front(root->right);
				}
			}
		}
		result.push_back(level);
	}
	return result;
}

TreeNode* buildTree(vector<int>& pre, int ps, int pe, vector<int>& in, int is, int ie, unordered_map<int, int> map)
{
	if (ps > pe || is > ie)
	{
		return NULL;
	}

	TreeNode* root = new TreeNode(pre[ps]);
	int rootIndex = map[root->val];
	int remaining = rootIndex - is;

	root->left = buildTree(pre, ps + 1, ps + remaining, in, is, rootIndex - 1, map);
	root->right = buildTree(pre, ps + remaining + 1, pe, in, rootIndex + 1, ie, map);

	return root;
}

TreeNode* buildTree(vector<int>& pre, vector<int>& in)
{
	int len = in.size();
	unordered_map<int, int> map;

	for (int i = 0; i < len; ++i)
	{
		map[in[i]] = i;
	}

	return buildTree(pre, 0, len - 1, in, 0, len - 1, map);
}

void connect(TreeNode* root)
{
	while (root->left)
	{
		TreeNode* p = root;

		while (p)
		{
			p->left->next = p->right;

			if (p->next)
			{
				p->right->next = p->next->left;
			}

			p = p->next;
		}
		root = root->left;
	}
}

// word ladder
int ladderLength(string beginWord, string endWord, unordered_set<string>& wordDict)
{
	unordered_set<string> head, tail, *phead, *ptail;

	head.insert(beginWord);
	tail.insert(endWord);
	int dist = 2;

	while (!head.empty() && !tail.empty())
	{
		if (head.size() < tail.size())
		{
			phead = &head;
			ptail = &tail;
		}
		else
		{
			phead = &tail;
			ptail = &head;
		}

		unordered_set<string> temp;
		for (auto iter = phead->begin(); iter != phead->end(); ++iter)
		{
			string word = *iter;
			wordDict.erase(word);
			
			for (int p = 0; p < word.length(); ++p)
			{
				char c = word[p];
				for (int k = 0; k < 26; ++k)
				{
					word[p] = 'a' + k;
					if (ptail->find(word) != ptail->end())
					{
						return dist;
					}
					if (wordDict.find(word) != wordDict.end())
					{
						temp.insert(word);
						wordDict.erase(word);
					}
				}
				word[p] = c;
			}
		}
		dist++;
		unordered_set<string> t = temp;
		temp = *phead;
		*phead = t;
	}
	return 0;
}

void dummyFill(vector<vector<char>>& board, int i, int j, int r, int c)
{
	if (i < 0 || i > r - 1 || j < 0 || j > c - 1)
	{
		return;
	}

	if (board[i][j] == 'O')
	{
		board[i][j] == 'A';
		dummyFill(board, i - 1, j, r, c);
		dummyFill(board, i + 1, j, r, c);
		dummyFill(board, i, j - 1, r, c);
		dummyFill(board, i, j + 1, r, c);
	}
}

void fixDummyFill(vector<vector<char>>& board, int r, int c)
{
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (board[i][j] == 'A')
			{
				board[i][j] = 'O';
			}
		}
	}
}

void solve(vector<vector<char>>& board)
{
	if (board.empty())
	{
		return;
	}

	int r = board.size();
	int c = board[0].size();

	if (r < 3 || c < 3)
	{
		return;
	}

	for (int i = 0; i < r; ++i)
	{
		if (board[i][0] == 'O')
		{
			dummyFill(board, i, 0, r, c);
		}
		if (board[i][c - 1] == 'O')
		{
			dummyFill(board, i, c - 1, r, c);
		}
	}

	for (int j = 0; j < c; ++j)
	{
		if (board[0][j] == 'O')
		{
			dummyFill(board, 0, j, r, c);
		}
		if (board[r - 1][j] == 'O')
		{
			dummyFill(board, r - 1, j, r, c);
		}
	}

	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (board[i][j] == 'O')
			{
				board[i][j] = 'X';
			}
		}
	}

	fixDummyFill(board, r, c);
}

bool isPalindrome(string str, int s, int e)
{
	while (s <= e)
	{
		if (str[s++] != str[e--])
		{
			return false;
		}
	}
	return true;
}

void dfs(int index, string str, vector<string>& path, vector<vector<string>>& ret)
{
	if (index == str.size())
	{
		ret.push_back(path);
		return;
	}

	for (int i = index; i < str.size(); ++i)
	{
		if (isPalindrome(str, index, i))
		{
			path.push_back(str.substr(index, i - index + 1));
			dfs(i + 1, str, path, ret);
			path.pop_back();
		}
	}
}

vector<vector<string>> partition(string str)
{
	vector<vector<string>> ret;
	
	if (str.empty() || str.size() == 0)
	{
		return ret;
	}
	
	vector<string> path;
	dfs(0, str, path, ret);
	
	return ret;
}

int canCompleteCurcuit(vector<int>& gas, vector<int>& cost)
{
	int n = gas.size();

	int begin = 0, end = begin, stationsVisited = 0, fuel = 0;

	while (stationsVisited < n)
	{
		int residual = fuel + (gas[end] - cost[end]);

		if (residual > 0)
		{
			fuel += gas[end] - cost[end];
			end = (end + 1) % n;
		}
		else
		{
			begin = (begin - 1 + n) % n;
			fuel += gas[begin] - cost[begin];
		}

		stationsVisited++;
	}

	return (fuel >= 0) ? begin : -1;
}

bool wordBreak(vector<string>& dict, string s)
{
	vector<bool> flag(s.size() + 1);
	
	flag[0] = true;

	for (int i = 1; i <= s.size(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (flag[j] && std::find(dict.begin(), dict.end(), s.substr(j, i)) != dict.end())
			{
				flag[i] = true;
			}
			break;
		}
	}

	return flag[s.size()];
}

int main()
{
	// is valid chars
	/*int de = numDecodings("121");*/

	//unordered_set<string> wordList = { "hot", "dot", "dog", "lot", "log", "cog" };
	//string beginWord = "hit";
	//string endWord = "cog";

	//int wres = ladderLength(beginWord, endWord, wordList);

	string str = "aab";
	vector<vector<string>> ans = partition(str);

	string s1 = "leetcode";
	vector<string> dict1 = { "leet", "code" };

	string s2 = "applepenapple";
	vector<string> dict2 = { "apple", "pen" };

	string s3 = "catsandog";
	vector<string> dict3 = { "cats", "dog", "sand", "and", "cat" };

	bool flag = wordBreak(dict1, s1);

	// climbing stairs;

	//int f = climbingStairs(10);
	//int e = climbingStairsNoDP(14);

	// max area of water containers
	// vector<int> height = { 1, 2 };
	// int area = maxAreaContainer(height);

	//vector<int> nums = { -1, 0, 1, 2, -1, -4 };
	//vector<vector<int>> result = threeSum1(nums,0);

	//string digits = "2345";
	//vector<string> result = letterCombinations(digits);

	//ListNode* head = NULL;
	//int ints[] = { 1 };
	//head = insert(ints, 1);

	//head = removeNthFromEnd(head, 1);

	// vector<string> res = wellFormedParenthesis(3);

	//int d = divide(93, 9);
	//int d1 = divide(93, -9);
	//int d2 = divide(-93, 9);
	//int d3 = divide(-93, -9);
	//int d4 = divide(0, 9);
	//int d6 = divide(9, 9);
	//int d5 = divide(2147483648, -1);

	//vector<int> nums = { 3, 4, 5, 6, 7, 8, 9, 10, -5, -2 };
	//int i = search(nums, -5);

	//vector<int> nums = { 5,7,7,8,8,10 };
	//vector<int> emty = {};
	//vector<int> re = searchRange(emty, 11);

	//vector<vector<char>> board = {
	//	{'.', '8', '7', '6', '5', '4', '3', '2', '1'},
	//	{'2', '.', '.', '.', '.', '.', '.', '.', '.'},
	//	{'3', '.', '.', '.', '.', '.', '.', '.', '.'},
	//	{'4', '.', '.', '.', '.', '.', '.', '.', '.'},
	//	{'5', '.', '.', '.', '.', '.', '.', '.', '.'},
	//	{'6', '.', '.', '.', '.', '.', '.', '.', '.'},
	//	{'7', '.', '.', '.', '.', '.', '.', '.', '.'},
	//	{'8', '.', '.', '.', '.', '.', '.', '.', '.'},
	//	{'9', '.', '.', '.', '.', '.', '.', '.', '.'}
	//};

	//bool res = validSudokuAccepted(board);

	//vector<int> n = { 1,2,3 };
	//vector<vector<int>> nans = permute(n);

	//vector<vector<int>> matrix = 
	//{
	//	{ 5,1,9,11 },
	//    { 2,4,8,10 },
	//	{ 13,3,6,7 },
	//	{ 15,14,12,16 }
	//};

	//rotate(matrix);

	//string slower = "aditya";
	//vector<bool> flags(26, false);
	//for (int i = 0; i < slower.length(); ++i)
	//{
	//	flags[(slower[i] - 'a')] = true;
	//}

	//vector<string> svec = { "eat", "tea", "tan", "ate", "nat", "bat" };
	//vector<string> sv = { "aaa", "aa" };
	//vector<vector<string>> svevResults = groupAnagrams(sv);

	// double ans = myPow(34.00515, -3);

	//vector<vector<int>> mat;
	//auto vvv = spiralOrder(mat);

	//vector<int> j1 = { 2,3,1,1,4 };
	//vector<int> j2 = { 3,2,1,0,4 };

	//bool canj = canJump(j1);
	//cout << canj << endl;
	//canj = canJump(j2);
	//cout << canj << endl;

	//vector<Interval> ins = { Interval(2,6), Interval(1,3), Interval(8,10), Interval(15,18) };
	//vector<Interval> ress = mergeIntervals(ins);

	//int uni = uniquePaths(100, 100);

	//vector<int> v = { 1, 2, 2, 2, 2, 2, 2, 2, 1, 0,0,0,0,0,1,1,1,0,2,1,0 };
	//sortColors(v);

	//TreeNode* p = NULL;
	////p = insertTree(p, 2);
	////p = insertTree(p, 1);
	////p = insertTree(p, 3);

	//p = insertTree(p, 10);
	//p = insertTree(p, 5);
	//p = insertTree(p, 15);
	//p = insertTree(p, 6);
	//p = insertTree(p, 20);

	//isValidBST(p);

	//TreeNode* q = NULL;
	//q = insertTree(q, 2);
	//q = insertTree(q, 1);
	//q = insertTree(q, 3);
	//q = insertTree(q, 6);

	//bool result = isSameTree(p, q);

	//TreeNode* root = new TreeNode(1);
	//root->left = new TreeNode(2);
	//root->right = new TreeNode(2);
	//root->left->left = new TreeNode(3);
	//root->left->right = new TreeNode(4);
	//root->right->left = new TreeNode(4);
	//root->right->right = new TreeNode(3);

	//TreeNode* root1 = new TreeNode(1);

	//root1->left = new TreeNode(2);
	//root1->right = new TreeNode(2);
	//root1->right->right = new TreeNode(3);
	//root1->left->right = new TreeNode(3);
	//bool result = isSymmetric(NULL);

	//int depth = maxTreeDepth(root1);

	// vector<vector<int>> result = levelOrderBottom(root);

	//vector<int> v = { -5, -2, 0, 5, 8, 15 };
	//TreeNode* sortedRoot = sortedArrayToBST(v);

	//ListNode* head1 = new ListNode(3);
	//ListNode* h1 = head1;
	//h1->next = new ListNode(7);
	//h1 = h1->next;
	//h1->next = new ListNode(8);

	//ListNode* head2 = new ListNode(4);
	//ListNode* h2 = head2;
	//h2->next = new ListNode(8);
	//h2 = h2->next;
	//h2->next = new ListNode(7);
	//h2 = h2->next;
	//h2->next = new ListNode(7);

	//ListNode* result = addTwoNumber(head1, head2);

	//string s1 = "abcabcbb";
	//string s2 = "bbbb";
	//string s3 = "abba";

	//int res = lengthOfLongestSubstring(s1);
	//int res1 = lengthOfLongestSubstring(s2);
	//int res2 = lengthOfLongestSubstring(s3);


	//bool result = compareBinHex("111011", "3B");

	// plus one
	//vector<int> vec = {0};
	//plusOne(vec);

	// int sq = sqrtNewton(8);

	/*std::cout << "addIntegersRecursively " << addIntegersRecursively(5) << std::endl;
	std::cout << "addIntegersIter " << addIntegersIter(5) << std::endl;*/

	// two sum
	//std::vector<int> nums = { 5, 9, 4, 2, 8, 97 };
	//std::vector<int> result = ::twoSum(nums, 101);

	// reverse
	//int ans = reverse(569);
	//cout << ans;

	// isPalindrome
	//bool flag = isPalindrome(-1);
	//cout << flag;

	//int r = ::romanToInt("MDCDLCVIII");
	//cout << r << endl;

	// isparanthesisvalid
	//bool flag = ::isParanthesisValid("(])");
	//cout << flag;

	#pragma region trie test
	
	//trie* tree = new trie();
	//vector<string> strs = {
	//	"leetcode",
	//	"leets",
	//	"leeter",
	//	"levis",
	//	"aditya",
	//	"nandita",
	//	"myra",
	//	"inter",
	//	"interception",
	//	"integer",
	//	"interpretation"
	//};

	//buildTrie(tree, strs);

	//tree->search("levis");

#pragma endregion

	#pragma region linkedlist

	//ListNode* head1 = NULL;
	//ListNode* head2 = NULL;

	//int ints1[4] = { 1, 1, 3, 4 };
	//int ints2[4] = { 1, 2, 2, 4 };

	//head1 = insert(ints1, 4);
	//head2 = insert(ints2, 4);

	//mergeTwoLists(head1, head2);


#pragma endregion

	// remove duplicates
	//vector<int> ia = { 1, 2, 2, 3, 4, 4, 4, 6, 9, 23 };
	//vector<int> ib = { 1, 2, 2, 4 };
	//vector<int> ic = {};
	//int size = removeDuplicates(ic);
	//int s = removeDuplicatesv3(ia);
	//int s1 = removeDuplicatesv3(ib);
	//int s2 = removeDuplicatesv3(ic);

	//int re = removeElement(ic, 2);
	//int re1 = removeElementv2(ia, 4);

	//string haystack = "mississippi";
	//string needle = "issip";
	//int index = strStr(haystack, needle);

	//searchInsert
	//vector<int> nums1 = { 1,3,5,6 };
	//int index = binarySearchNumber(nums1, 7);
	//index = binarySearchNumber(nums1, 0);

	// isBadVersion
	//vector<int> versions = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };
	//int v = firstBadVersion(26);

	// count and say
	//string say = countAndSay(4);
	//cout << say << endl;

	// max sub array sum
	//vector<int> a = { -2,1,-3,4,-1,2,1,-5,4 };
	//int sum = maxSubArraySum(a, 0, a.size() - 1);

	// length of last word
	//string s = "this ";
	//string s1 = "";
	//string s2 = "     ";
	//string s3 = "1     ";
	//string s4 = "this";
	//int len = lengthOfLastWord(s);
	// len = lengthOfLastWord(s1);
	// len = lengthOfLastWord(s2);
	// len = lengthOfLastWord(s3);
	// len = lengthOfLastWord(s4);

	int x;
	std::cin >> x;
	return 0;
}