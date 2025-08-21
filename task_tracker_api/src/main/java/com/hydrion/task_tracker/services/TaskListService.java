package com.hydrion.task_tracker.services;

import com.hydrion.task_tracker.domain.entities.TaskList;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

public interface TaskListService {
    List<TaskList> findTaskLists();
    TaskList createTaskList(TaskList tasklist);
    Optional<TaskList> getTaskListById(UUID id);
    TaskList updateTasklist(UUID id,TaskList tasklist);
    void deleteTaskList(UUID taskListId);
}
