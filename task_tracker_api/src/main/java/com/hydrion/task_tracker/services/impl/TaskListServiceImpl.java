package com.hydrion.task_tracker.services.impl;

import com.hydrion.task_tracker.domain.entities.TaskList;
import com.hydrion.task_tracker.repositories.TaskListRepository;
import com.hydrion.task_tracker.services.TaskListService;
import jakarta.transaction.Transactional;
import org.springframework.cglib.core.Local;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;
import java.util.UUID;

@Service
public class TaskListServiceImpl implements TaskListService {
    private TaskListRepository taskListRepository;

    public TaskListServiceImpl(TaskListRepository taskListRepository){
        this.taskListRepository = taskListRepository;
    }
    @Override
    public List<TaskList> findTaskLists() {
        return taskListRepository.findAll();
    }

    @Override
    public TaskList createTaskList(TaskList tasklist) {
        if(null != tasklist.getId()){ // or optionally just unset the id
            throw new IllegalArgumentException("Task list already exists");
        }
        if(null == tasklist.getTitle() || tasklist.getTitle().isBlank()){
            throw new IllegalArgumentException("Task list title must be present");
        }
        LocalDateTime now = LocalDateTime.now();
        tasklist.setCreated(now);
        tasklist.setUpdated(now);
        return taskListRepository.save(tasklist);
    }

    @Override
    public void deleteTaskList(UUID taskListId) {
        taskListRepository.deleteById(taskListId);
    }

    @Override
    public Optional<TaskList> getTaskListById(UUID id) {
        return taskListRepository.findById(id);
    }

    @Transactional
    @Override
    public TaskList updateTasklist(UUID id, TaskList tasklist) {
        TaskList retrievedTaskL = taskListRepository.findById(id).orElseThrow(()->new IllegalArgumentException("Task list does not exist in order to be updated"));
        retrievedTaskL.setTitle(tasklist.getTitle());
        retrievedTaskL.setDescription(tasklist.getDescription());
        retrievedTaskL.setUpdated(LocalDateTime.now());
        return taskListRepository.save(retrievedTaskL);
    }
}
