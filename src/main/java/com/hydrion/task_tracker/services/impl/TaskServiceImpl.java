package com.hydrion.task_tracker.services.impl;

import com.hydrion.task_tracker.domain.entities.Task;
import com.hydrion.task_tracker.domain.entities.TaskList;
import com.hydrion.task_tracker.domain.entities.TaskPriority;
import com.hydrion.task_tracker.domain.entities.TaskStatus;
import com.hydrion.task_tracker.repositories.TaskListRepository;
import com.hydrion.task_tracker.repositories.TaskRepository;
import com.hydrion.task_tracker.services.TaskService;
import jakarta.transaction.Transactional;
import org.springframework.cglib.core.Local;
import org.springframework.core.io.support.ResourcePatternResolver;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;
import java.util.UUID;

@Service
public class TaskServiceImpl implements TaskService {
    private final ResourcePatternResolver resourcePatternResolver;
    private final TaskRepository taskRepository;
    private final TaskListRepository taskListRepository;

    public TaskServiceImpl(ResourcePatternResolver resourcePatternResolver, TaskRepository taskRepository, TaskListRepository taskListRepository) {
        this.resourcePatternResolver = resourcePatternResolver;
        this.taskRepository = taskRepository;
        this.taskListRepository = taskListRepository;
    }

    @Override
    public List<Task> getAllTasks(UUID taskListId) {
        return this.taskRepository.findByTaskListId(taskListId);
    }

    @Transactional
    @Override
    public Task createTask(UUID taskListId, Task task) {
        if(null != task.getId()){
            throw new IllegalArgumentException("Task already exists");
        }
        if(null == task.getTitle() || task.getTitle().isBlank()){
            throw new IllegalArgumentException("Task must have a title");
        }
        TaskPriority priority = Optional.ofNullable(task.getPriority()).orElse(TaskPriority.MEDIUM);
        TaskList taskList = taskListRepository.findById(taskListId).orElseThrow(()-> new IllegalArgumentException("Task list does not exist, cannot assign a task"));
        task.setTaskList(taskList);
        task.setPriority(priority);
        task.setStatus(TaskStatus.OPEN);
        LocalDateTime now = LocalDateTime.now();
        task.setUpdated(now);
        task.setCreated(now);
        return taskRepository.save(task);
    }

    @Override
    public Task getTaskById(UUID taskListId, UUID taskId) {
        return taskRepository.findByTaskListIdAndId(taskListId, taskId).orElse(null);
    }

    @Transactional
    @Override
    public Task updateTask(UUID taskListId, UUID taskId, Task task) {
        Task existingTask = taskRepository.findByTaskListIdAndId(taskListId, taskId).orElse(null);
        existingTask.setUpdated(LocalDateTime.now());
        existingTask.setStatus(task.getStatus());
        existingTask.setPriority(task.getPriority());
        existingTask.setDescription(task.getDescription());
        existingTask.setTitle(task.getTitle());
        return taskRepository.save(existingTask);
    }

    @Transactional
    @Override
    public void deleteTask(UUID taskListId, UUID taskId) {
        taskRepository.deleteByTaskListIdAndId(taskListId, taskId);
    }
}
