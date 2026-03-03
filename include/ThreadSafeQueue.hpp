#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

namespace quant {
    template <typename T>
    class ThreadSafeQueue {
    private:
        std::queue<T> queue;
        mutable std::mutex mutex;
        std::condition_variable cv;
        bool finished = false;

    public:
        void push(T value) {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(std::move(value));
            cv.notify_one(); // Wake up the consumer
        }

        bool pop(T& value) {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [this] { return !queue.empty() || finished; });

            if (queue.empty()) return false;

            value = std::move(queue.front());
            queue.pop();
            return true;
        }

        void setFinished() {
            std::lock_guard<std::mutex> lock(mutex);
            finished = true;
            cv.notify_all();
        }
    };
}