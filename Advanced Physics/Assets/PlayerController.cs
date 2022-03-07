using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    CharacterController cc;
    Vector2 moveInput = new Vector2();
    public Vector3 velocity;
    public float speed = 10;
    public float jumpVelocity = 5;
    public bool isGrounded;
    bool jumpInput;

    // Start is called before the first frame update
    void Start()
    {
        cc = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        jumpInput = Input.GetButton("Jump");
    }

    void FixedUpdate()
    {
        Vector3 delta;
        delta = (moveInput.x * Vector3.right + moveInput.y * Vector3.forward) * speed * Time.fixedDeltaTime;
        
        if(jumpInput && isGrounded)
        {
            velocity.y = jumpVelocity;
        }

        if (isGrounded && velocity.y < 0)
        {
            velocity.y = 0;
        }
        velocity += Physics.gravity * Time.fixedDeltaTime;
        delta += velocity * Time.fixedDeltaTime;
        cc.Move(delta);
        isGrounded = cc.isGrounded;
    }
}