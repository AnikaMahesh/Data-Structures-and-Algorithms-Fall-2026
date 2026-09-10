def iou(b1, b2):
    """Calculate Intersection over Union between two normalized bboxes"""
    if len(b1) != 4 or len(b2) != 4:
        return 0.0
    ix1, iy1 = max(b1[0], b2[0]), max(b1[1], b2[1])
    ix2, iy2 = min(b1[2], b2[2]), min(b1[3], b2[3])
    inter = max(0, ix2-ix1) * max(0, iy2-iy1)
    a1 = (b1[2]-b1[0]) * (b1[3]-b1[1])
    a2 = (b2[2]-b2[0]) * (b2[3]-b2[1])
    union = a1 + a2 - inter
    print(inter, union)
    return inter / union if union > 0 else 0.0


assert "test1", iou([1,1,1,1], [1,1,1,1]) == 0.0
assert "test2", iou([0.1,0.1,0.3,0.3], [0.1,0.1,0.3,0.3]) == 1.0
assert "test3", iou([0.1,0.1,0.3,0.3], [0.4,0.4,0.5,0.5]) == 0.0
assert "test4", iou([0.1,0.1,0.3,0.3], [0.3,0.3,0.5,0.5]) == 0.0
assert "test5", iou([0.1,0.1,0.3,0.3], [0.2,0.2,0.4,0.4]) == 0.14285714285714277
assert "test6", iou([0.1,0.2,0.3,0.4], [0.2,0.3,0.4,0.5]) == 0.14285714285714288
assert "test7", iou([0.1,0.1,0.9,0.9], [0.2,0.2,0.4,0.4]) == 0.0625