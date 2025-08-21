package com.hydrion.task_tracker.services;

import com.hydrion.task_tracker.domain.entities.Task;

import java.util.List;
import java.util.UUID;

public interface TaskService {
    List<Task> getAllTasks(UUID taskListId);
    Task createTask(UUID taskListId, Task task);
    Task getTaskById(UUID taskListId, UUID taskId);
    Task updateTask(UUID taskListId, UUID taskId, Task task);
    void deleteTask(UUID taskListId, UUID taskId);
}
