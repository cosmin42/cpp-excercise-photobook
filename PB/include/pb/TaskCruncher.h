#pragma once

#include <string>

#include <pb/tasks/ParallelTaskConsumer.h>

#include <pb/MapReducer.h>

namespace PB {
class TaskCruncher final {
public:
  TaskCruncher() = default;
  ~TaskCruncher() = default;

  TaskCruncher(const TaskCruncher &) = delete;
  TaskCruncher &operator=(const TaskCruncher &) = delete;
  TaskCruncher(TaskCruncher &&) = delete;

  void registerPTC(const std::string poolName, unsigned thrreadsCount);

  void crunch(const std::string poolName, MapReducer &mapper);

  void abort();

private:
  std::stop_source mStopSource;
  std::unordered_map<std::string, std::unique_ptr<PBDev::ParallelTaskConsumer>>
      mPTC;
};
} // namespace PB