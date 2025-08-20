package com.hydrion.task_tracker.mappers;

import com.hydrion.task_tracker.domain.dto.TaskDto;
import com.hydrion.task_tracker.domain.entities.Task;

public interface TaskMapper {
    Task fromDto(TaskDto dto);
    TaskDto toDto(Task task);
}
