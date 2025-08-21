package com.hydrion.task_tracker.domain.dto;

import com.hydrion.task_tracker.domain.entities.TaskPriority;
import com.hydrion.task_tracker.domain.entities.TaskStatus;

import java.time.LocalDateTime;
import java.util.UUID;

public record TaskDto(UUID id,
                    String title,
                    String description,
                    LocalDateTime dueDate,
                    TaskPriority priority,
                    TaskStatus status
) {
}
