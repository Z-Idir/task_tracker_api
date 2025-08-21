package com.hydrion.task_tracker.controllers;

import com.hydrion.task_tracker.domain.dto.TaskListDto;
import com.hydrion.task_tracker.domain.entities.TaskList;
import com.hydrion.task_tracker.mappers.TaskListMapper;
import com.hydrion.task_tracker.services.TaskListService;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

@RestController
@RequestMapping(path = "/api/task-lists")
public class TaskListController {
    private final TaskListService taskListService;
    private final TaskListMapper taskListMapper;

    public TaskListController(TaskListService taskListService, TaskListMapper taskListMapper) {
        this.taskListService = taskListService;
        this.taskListMapper = taskListMapper;
    }

    @GetMapping
    public List<TaskListDto> getTaskLists(){
        return taskListService.findTaskLists()
                .stream()
                .map(taskListMapper::toDto)
                .toList();
    }

    @PostMapping
    public TaskListDto createTaskList(@RequestBody TaskListDto taskListDto){
        TaskList taskList = taskListMapper.fromDto(taskListDto);
        return taskListMapper.toDto(taskListService.createTaskList(taskList));
    }

    @GetMapping(path = "/{task_list_id}")
    public TaskListDto getTaskListById(@PathVariable(name = "task_list_id") UUID taskListId){
        return taskListService.getTaskListById(taskListId).map(taskListMapper::toDto)
                .orElse(null);
    }

    @PutMapping("/{task_list_id}")
    public TaskListDto updateTaskList(@PathVariable(name = "task_list_id") UUID taskListId, @RequestBody TaskListDto taskListDto){
        return taskListMapper
                .toDto(
                        taskListService.updateTasklist(taskListId, taskListMapper.fromDto(taskListDto)));
    }

    @DeleteMapping(path = "/{task_list_id}")
    public void deleteTaskList(@PathVariable(name = "task_list_id")UUID taskListId){
        taskListService.deleteTaskList(taskListId);
    }


}
