package com.hydrion.task_tracker.mappers.impl;

import com.hydrion.task_tracker.domain.dto.TaskListDto;
import com.hydrion.task_tracker.domain.entities.Task;
import com.hydrion.task_tracker.domain.entities.TaskList;
import com.hydrion.task_tracker.domain.entities.TaskStatus;
import com.hydrion.task_tracker.mappers.TaskListMapper;
import com.hydrion.task_tracker.mappers.TaskMapper;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Component
public class TaskListMapperImpl implements TaskListMapper {

    private TaskMapper taskMapper;

    public TaskListMapperImpl(TaskMapper taskMapper){
        this.taskMapper = taskMapper;
    }


    @Override
    public TaskList fromDto(TaskListDto dto) {
        return TaskList.builder()
                .id(dto.id())
                .title(dto.title())
                .description(dto.description())
                .tasks(Optional.ofNullable(dto.tasks())
                        .map(tasks -> tasks.stream()
                                .map(taskMapper::fromDto)
                                .toList()
                                ).orElse(null))
                .created(null)
                .updated(null)
                .build();
    }



    @Override
    public TaskListDto toDto(TaskList taskList) {
        return new TaskListDto(
                taskList.getId(),
                taskList.getTitle(),
                taskList.getDescription(),
                Optional.ofNullable(taskList.getTasks())
                        .map(List::size)
                        .orElse(0),
                this.calculateTaskListProgress(taskList.getTasks()),
                Optional.ofNullable(taskList.getTasks())
                        .map(tasks -> tasks.stream().map(taskMapper::toDto).toList())
                        .orElse(null)
        );
    }


    private Double calculateTaskListProgress(List<Task> tasks){
        if(tasks == null) {
            return null;
        }
        long closedTaskCount = tasks.stream()
                .filter(task -> TaskStatus.CLOSED == task.getStatus())
                .count();
        return (double) closedTaskCount / tasks.size();
    }
}
