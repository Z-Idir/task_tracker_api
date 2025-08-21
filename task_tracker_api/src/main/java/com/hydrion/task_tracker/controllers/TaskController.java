package com.hydrion.task_tracker.controllers;

import com.hydrion.task_tracker.domain.dto.TaskDto;
import com.hydrion.task_tracker.mappers.TaskMapper;
import com.hydrion.task_tracker.services.TaskService;
import lombok.extern.java.Log;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.UUID;

@RestController
@RequestMapping(path = "/api/task-lists/{task_list_id}/tasks")
@Log
public class TaskController {
    private TaskService taskService;
    private TaskMapper taskMapper;

    public TaskController(TaskService taskService, TaskMapper taskMapper) {
        this.taskService = taskService;
        this.taskMapper = taskMapper;
    }

    @GetMapping
    public List<TaskDto> getTasks(@PathVariable(name = "task_list_id") UUID taskListId){
        return taskService.getAllTasks(taskListId).stream().map(task -> taskMapper.toDto(task)).toList();
    }

    @PostMapping
    public TaskDto createTask(@PathVariable(name = "task_list_id") UUID taskListId, @RequestBody TaskDto taskDto){
        return taskMapper.toDto(taskService.createTask(taskListId, taskMapper.fromDto(taskDto)));
    }

    @DeleteMapping(path = "/{task_id}")
    public void deleteTask(@PathVariable(name = "task_list_id") UUID taskListId, @PathVariable(name = "task_id") UUID taskId){
        taskService.deleteTask(taskListId, taskId);
    }

    @GetMapping(path = "/{task_id}")
    public TaskDto getTask(@PathVariable(name = "task_list_id") UUID taskListId, @PathVariable(name = "task_id") UUID taskId){
        return taskMapper.toDto(taskService.getTaskById(taskListId, taskId));
    }

    @PutMapping(path = "/{task_id}")
    public TaskDto updateTask(@PathVariable(name = "task_list_id") UUID taskListId,
                              @PathVariable(name = "task_id") UUID taskId,
                              @RequestBody TaskDto taskDto
                              ){
        log.info(taskDto.toString());
        return taskMapper.toDto(taskService.updateTask(taskListId, taskId, taskMapper.fromDto(taskDto)));
    }

}
