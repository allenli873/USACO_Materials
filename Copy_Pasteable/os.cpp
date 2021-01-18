#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// IMPORTANT: less_equal for multiset functionality
// also, when using less_equal, use os.erase(os.upper_bound(num)) to erase the number
// find seems broken and lower bound and upper bound are switched with less_equal
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
