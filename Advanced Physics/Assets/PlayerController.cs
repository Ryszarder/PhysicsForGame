using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    CharacterController cc;
    public Transform cam;
    Animator animator;

    Vector2 moveInput = new Vector2();
    public Vector3 velocity;
    public Vector3 hitDirection;

    public float speed = 10;
    public float jumpVelocity = 5;
    public float fallMulitplier = 3;
    public float lowJumpMultiplier = 1.5f;

    public bool isGrounded;
    bool jumpInput;

    // Start is called before the first frame update
    void Start()
    {
        cc = GetComponent<CharacterController>();
        if(cam == null)
        {
            cam = Camera.main.transform;
        }

        animator = GetComponentInChildren<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        moveInput.x = Input.GetAxis("Horizontal");
        moveInput.y = Input.GetAxis("Vertical");
        jumpInput = Input.GetButton("Jump");

        animator.SetFloat("Forwards", moveInput.y);
        animator.SetBool("Jump", !isGrounded);
    }

    void FixedUpdate()
    {
        Vector3 delta;

        Vector3 camForward = cam.forward;
        camForward.y = 0;
        camForward.Normalize();

        Vector3 camRight = cam.right;
        transform.forward = camForward;

        delta = (moveInput.x * camRight + moveInput.y * camForward) * speed;

        if(isGrounded || moveInput.x != 0 || moveInput.y != 0)
        {
            velocity.x = delta.x;
            velocity.z = delta.z;
        }
        
        if(jumpInput && isGrounded)
        {
            velocity.y = jumpVelocity;
        }

        if (isGrounded && velocity.y < 0)
        {
            velocity.y = 0;
        }

        velocity += Physics.gravity * Time.fixedDeltaTime;

        if(velocity.y < 0)
        {
            velocity += Physics.gravity * fallMulitplier * Time.fixedDeltaTime;
        }
        else if(velocity.y > 0 && !jumpInput)
        {
            velocity += Physics.gravity * lowJumpMultiplier * Time.fixedDeltaTime;
        }

        if(!isGrounded)
        {
            hitDirection = Vector3.zero;
        }

        if(moveInput.x == 0 && moveInput.y == 0)
        {
            Vector3 horizontalHitDirection = hitDirection;
            hitDirection.y = 0;
            float displacement = horizontalHitDirection.magnitude;
            if(displacement > 0)
            {
                velocity -= 0.2f * horizontalHitDirection / displacement;
            }
        }
        cc.Move(velocity * Time.deltaTime);
        isGrounded = cc.isGrounded;
    }

    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        hitDirection = hit.point - transform.position;
    }
}