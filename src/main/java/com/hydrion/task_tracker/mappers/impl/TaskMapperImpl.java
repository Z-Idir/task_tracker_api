package com.hydrion.task_tracker.mappers.impl;

import com.hydrion.task_tracker.domain.dto.TaskDto;
import com.hydrion.task_tracker.domain.entities.Task;
import com.hydrion.task_tracker.mappers.TaskMapper;
import org.springframework.stereotype.Component;

@Component
public class TaskMapperImpl implements TaskMapper {
    @Override
    public Task fromDto(TaskDto dto) {
        return Task.builder()
                .id(dto.id())
                .title(dto.title())
                .description(dto.description())
                .dueDate(dto.dueDate())
                .status(dto.status())
                .priority(dto.priority())
                .taskList(null)
                .created(null)
                .updated(null)
                .build();
    }

    @Override
    public TaskDto toDto(Task task) {
        return new TaskDto(task.getId(),
                task.getTitle(),
                task.getDescription(),
                task.getDueDate(),
                task.getPriority(),
                task.getStatus());
    }
}
