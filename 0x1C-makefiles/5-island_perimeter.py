#!/usr/bin/python3
"""Defines an island perimeter measuring function."""

def island_perimeter(grid):
    """
    Calculates the perimeter of the island described in the grid.

    Args:
        grid (list[list[int]]): A rectangular grid representing the island.

    Returns:
        int: The perimeter of the island.

    Examples:
        >>> island_perimeter([[0, 1, 0, 0],
        ...                   [1, 1, 1, 0],
        ...                   [0, 1, 0, 0],
        ...                   [1, 1, 0, 0]])
        16
    """
    rows = len(grid)
    if rows == 0:
        return 0

    cols = len(grid[0])
    perimeter = 0

    for i in range(rows):
        for j in range(cols):
            if grid[i][j] == 1:
                perimeter += 4  # Start with the assumption that all sides are exposed

                # Check the neighboring cells
                if i > 0 and grid[i - 1][j] == 1:
                    perimeter -= 1  # Subtract one side as it is shared
                if i < rows - 1 and grid[i + 1][j] == 1:
                    perimeter -= 1
                if j > 0 and grid[i][j - 1] == 1:
                    perimeter -= 1
                if j < cols - 1 and grid[i][j + 1] == 1:
                    perimeter -= 1

    return perimeter
