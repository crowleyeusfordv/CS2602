#include <iostream>
#include <queue> // 包含优先队列的头文件
#include <vector>

// 定义 Post 结构体
struct Post {
    int id;    // 帖子的 ID
    int day;   // 帖子第几天对应的浏览量
    int views; // 帖子的浏览量
	Post(int id, int day, int views) : id(id), day(day), views(views) {};
};

// 自定义比较函数，用于根据浏览量对优先队列进行排序
struct CompareViews {
	bool operator()(const Post& a, const Post& b) {
		if (a.views == b.views) {
			return a.id < b.id; // 当浏览量相同时，ID 较大的优先
		}
		return a.views < b.views; // 按照浏览量从大到小排序
	}
};

int main()
{
    int T, D, P;//表示需要统计每天对应的最近 T 天内单日浏览量最高的帖子,D、P分别表示最大天数和总帖子数。
	// 创建一个优先队列，使用自定义比较函数
	std::priority_queue<Post, std::vector<Post>, CompareViews> pq;
	std::cin >> T;
	std::cin >> D >> P;
	int *rst = new int[D];
	for (int i = 0; i < D; i++) {
		rst[i] = -1; // 初始化 rst 数组
	}
	for (int i = 1; i <= D; i++) {
		for (int j = 1; j <= P; j++) {
			int views_;
			std::cin >> views_;
			Post post(j, i, views_);
			pq.push(post);
		}
		// 输出每天的热门贴
		while (!pq.empty()) {
			Post post = pq.top();
			if (post.day <= i && post.day >= i - T + 1) {
				rst[i - 1] = post.id;
				break;
			}
			pq.pop();
		}
	}

	for (int i = 0; i < D; i++) {
		std::cout << rst[i] << " ";
	}
	delete[] rst;
    return 0;
}
