package com.hydrion.task_tracker.mappers;

import com.hydrion.task_tracker.domain.dto.TaskListDto;
import com.hydrion.task_tracker.domain.entities.TaskList;

public interface TaskListMapper {
    TaskList fromDto(TaskListDto dto);
    TaskListDto toDto(TaskList taskList);
}
