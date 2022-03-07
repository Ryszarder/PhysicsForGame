using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public Transform target;
    public float rotationSpeed = 180;
    public float distance = 4;
    public float currentDistance = 4;
    float backDistance = 4;
    float zoomSpeed = 5;
    float heightOffset = 1.8f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetMouseButton(1))
        {
            Vector3 angles = transform.eulerAngles;
            float dx = Input.GetAxis("Mouse Y");
            float dy = Input.GetAxis("Mouse X");

            angles.x = Mathf.Clamp(angles.x + dx * rotationSpeed * Time.deltaTime, 0, 70);

            angles.y -= dy * rotationSpeed * Time.deltaTime;
            transform.eulerAngles = angles;
        }

        if(Input.GetAxis("Mouse ScrollWheel") < 2)
        {
            backDistance = Mathf.Clamp(backDistance - Input.GetAxis("Mouse ScrollWheel") * zoomSpeed, 4, 10);
            distance = backDistance;
        }

        RaycastHit hit;
        if(Physics.Raycast(GetTargetPosition(), -transform.forward, out hit, distance))
        {
            currentDistance = hit.distance;
            backDistance = currentDistance;
        }
        else
        {
            currentDistance = Mathf.MoveTowards(currentDistance, distance, Time.deltaTime);
        }


        transform.position = GetTargetPosition() - currentDistance * transform.forward;
    }

    Vector3 GetTargetPosition()
    {
        return target.position + heightOffset * Vector3.up;
    }
}
