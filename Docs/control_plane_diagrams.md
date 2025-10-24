# NDMP 控制面结构概览

本节根据 `ndmpd` 守护进程的源码，总结核心控制面的结构体关系与模块依赖。下方 Mermaid 图可直接在支持 Mermaid 的渲染器中查看。

## 核心结构体类图

```mermaid
classDiagram
    class ndmpConnection {
        +int conn_sock
        +XDR conn_xdrs
        +ulong_t conn_my_sequence
        +boolean_t conn_authorized
        +boolean_t conn_eof
        +msg_info_t conn_msginfo
        +ushort_t conn_version
        +void* conn_client_data
        +mutex_t conn_lock
        +adt_session_data_t* conn_ah
    }

    class ndmpMsgHandler {
        +ndmp_msg_handler_func_t* mh_func
        +bool_t(*mh_xdr_request)(XDR*, ...)
        +int mh_sizeof_request
        +bool_t(*mh_xdr_reply)(XDR*, ...)
        +int mh_sizeof_reply
    }

    class ndmpHandler {
        +int hd_cnt
        +hd_messages[INT_MAXCMD]
    }

    class ndmpdSessionScsiDesc {
        +int sd_is_open
        +int sd_devid
        +boolean_t sd_valid_target_set
        +int sd_sid
        +int sd_lun
        +char sd_adapter_name[SCSI_MAX_NAME]
    }

    class ndmpdSessionTapeDesc {
        +int td_fd
        +ulong_t td_record_count
        +ndmp_tape_open_mode td_mode
        +u_longlong_t td_pos
        +int td_sid
        +int td_lun
        +char td_adapter_name[SCSI_MAX_NAME]
    }

    class ndmpdSessionMoverDesc {
        +ndmp_mover_state md_state
        +ndmp_mover_mode md_mode
        +ndmp_mover_pause_reason md_pause_reason
        +ndmp_mover_halt_reason md_halt_reason
        +u_longlong_t md_data_written
        +u_longlong_t md_seek_position
        +u_longlong_t md_bytes_left_to_read
        +u_longlong_t md_window_offset
        +u_longlong_t md_window_length
        +u_longlong_t md_position
        +boolean_t md_pre_cond
        +ulong_t md_record_size
        +ulong_t md_record_num
        +int md_listen_sock
        +int md_sock
        +ulong_t md_r_index
        +ulong_t md_w_index
        +char* md_buf
    }

    class ndmpdSessionDataModule {
        +void* dm_module_cookie
        +module_start_func_t* dm_start_func
        +module_abort_func_t* dm_abort_func
        +ndmpd_module_stats dm_stats
    }

    class ndmpdSessionDataDesc {
        +ndmp_data_operation dd_operation
        +boolean_t dd_abort
        +boolean_t dd_io_ready
        +ndmp_pval* dd_env
        +ulong_t dd_env_len
        +ulong_t dd_nlist_len
        +int dd_sock
        +u_longlong_t dd_read_offset
        +u_longlong_t dd_read_length
        +u_longlong_t dd_data_size
        +ndmpd_session_data_module_t dd_module
        +ndmp_data_state dd_state
        +ndmp_data_halt_reason dd_halt_reason
        +ndmp_name* dd_nlist
        +ndmp_mover_addr dd_mover
        +mem_ndmp_name_v3_t* dd_nlist_v3
        +ndmp_addr_v3 dd_data_addr
        +int dd_listen_sock
        +u_longlong_t dd_bytes_left_to_read
        +u_longlong_t dd_position
        +u_longlong_t dd_discard_length
        +ndmp_addr_v4 dd_data_addr_v4
    }

    class ndmpdSessionFileHistory {
        +ndmp_fh_unix_path* fh_path_entries
        +ndmp_fh_unix_dir* fh_dir_entries
        +ndmp_fh_unix_node* fh_node_entries
        +char* fh_path_name_buf
        +char* fh_dir_name_buf
        +ulong_t fh_path_index
        +ulong_t fh_dir_index
        +ulong_t fh_node_index
        +ulong_t fh_path_name_buf_index
        +ulong_t fh_dir_name_buf_index
    }

    class ndmpdSessionFileHistoryV3 {
        +ndmp_file_v3* fh_files
        +ndmp_dir_v3* fh_dirs
        +ndmp_node_v3* fh_nodes
        +ndmp_file_name_v3* fh_file_names
        +ndmp_file_name_v3* fh_dir_names
        +ndmp_file_stat_v3* fh_file_stats
        +ndmp_file_stat_v3* fh_node_stats
        +char* fh_file_name_buf
        +char* fh_dir_name_buf
        +ulong_t fh_file_index
        +ulong_t fh_dir_index
        +ulong_t fh_node_index
        +ulong_t fh_file_name_buf_index
        +ulong_t fh_dir_name_buf_index
    }

    class ndmpdFileHandler {
        +int fh_fd
        +ulong_t fh_mode
        +ulong_t fh_class
        +void* fh_cookie
        +ndmpd_file_handler_func_t* fh_func
        +ndmpd_file_handler* fh_next
    }

    class ndmpdModuleParams {
        +void* mp_daemon_cookie
        +void** mp_module_cookie
        +ushort_t mp_protocol_version
        +ndmp_data_operation mp_operation
        +ndmpd_module_stats* mp_stats
        +ndmpd_get_env_func_t* mp_get_env_func
        +ndmpd_add_env_func_t* mp_add_env_func
        +ndmpd_add_env_func_t* mp_set_env_func
        +ndmpd_get_name_func_t* mp_get_name_func
        +ndmpd_dispatch_func_t* mp_dispatch_func
        +ndmpd_done_func_t* mp_done_func
        +ndmpd_log_func_t* mp_log_func
        +ndmpd_add_file_handler_func_t* mp_add_file_handler_func
        +ndmpd_remove_file_handler_func_t* mp_remove_file_handler_func
        +ndmpd_write_func_t* mp_write_func
        +ndmpd_file_history_path_func_t* mp_file_history_path_func
        +ndmpd_file_history_dir_func_t* mp_file_history_dir_func
        +ndmpd_file_history_node_func_t* mp_file_history_node_func
        +ndmpd_read_func_t* mp_read_func
        +ndmpd_seek_func_t* mp_seek_func
        +ndmpd_file_recovered_func_t* mp_file_recovered_func
        +ndmpd_log_func_v3_t* mp_log_func_v3
    }

    class ndmpLbrParams {
        +NdmpdSession* nlp_session
        +int nlp_flags
        +ndmp_backup_params_t bk_params
        +ndmp_restore_params_t rs_params
        +ndmpd_module_params_t* nlp_params
        +tlm_job_stats_t* nlp_jstat
        +lbr_fhlog_call_backs_t* nlp_logcallbacks
        +tlm_commands_t nlp_cmds
        +int nlp_event.ev_nw
        +int nlp_event.ev_rv
        +cond_t nlp_cv
        +int nlp_flag
        +u_longlong_t nlp_bytes_total
    }

    class ndmpdSession {
        +ndmp_connection_t* ns_connection
        +boolean_t ns_eof
        +ushort_t ns_protocol_version
        +ndmpd_session_scsi_desc_t ns_scsi
        +ndmpd_session_tape_desc_t ns_tape
        +ndmpd_session_mover_desc_t ns_mover
        +ndmpd_session_data_desc_t ns_data
        +ndmpd_session_file_history_t ns_fh
        +ndmpd_file_handler_t* ns_file_handler_list
        +int ns_nref
        +ndmp_lbr_params_t* ns_ndmp_lbr_params
        +mutex_t ns_lock
        +ndmpd_session_file_history_v3_t ns_fh_v3
        +unsigned char ns_challenge[MD5_CHALLENGE_SIZE]
        +boolean_t ns_set_ext_list
        +hardlink_q* hardlink_q
    }

    ndmpdSession --> ndmpConnection : owns
    ndmpdSession --> ndmpdSessionScsiDesc : embeds
    ndmpdSession --> ndmpdSessionTapeDesc : embeds
    ndmpdSession --> ndmpdSessionMoverDesc : embeds
    ndmpdSession --> ndmpdSessionDataDesc : embeds
    ndmpdSession --> ndmpdSessionFileHistory : embeds
    ndmpdSession --> ndmpdSessionFileHistoryV3 : embeds
    ndmpdSession --> ndmpdFileHandler : tracks
    ndmpdSession --> ndmpLbrParams : references
    ndmpLbrParams --> ndmpdSession : back-pointer
    ndmpLbrParams --> ndmpdModuleParams : configures
    ndmpdSessionDataDesc --> ndmpdSessionDataModule : composes
    ndmpdSessionDataModule --> ndmpdModuleParams : uses stats
    ndmpdSessionDataDesc --> ndmpdSessionMoverDesc : coordinates
    ndmpHandler --> ndmpMsgHandler : aggregates
    ndmpConnection --> ndmpHandler : uses dispatch table
```

上述类图归纳了 `ndmpd` 控制面使用的关键结构体与嵌套关系。

## 控制面模块依赖图

```mermaid
graph TD
    ndmpdMain[ndmpd_main.c]
    ndmpdDoor[ndmpd_door.c]
    ndmpdProp[ndmpd_prop.c]
    ndmpdComm[ndmpd_comm.c]
    ndmpdHandler[ndmpd_handler.c]
    ndmpdConfig[ndmpd_config.c]
    ndmpdScsi[ndmpd_scsi.c]
    ndmpdTape[ndmpd_tape.c]
    ndmpdData[ndmpd_data.c]
    ndmpdMover[ndmpd_mover.c]
    ndmpdUtil[ndmpd_util.c]
    tlmLib[tlm_init.c / tlm_proto.h]

    ndmpdMain --> ndmpdProp
    ndmpdMain --> ndmpdDoor
    ndmpdMain --> tlmLib
    ndmpdMain --> ndmpdComm
    ndmpdComm --> ndmpdHandler
    ndmpdComm --> ndmpdData
    ndmpdComm --> ndmpdMover
    ndmpdComm --> ndmpdUtil
    ndmpdComm --> ndmpdDoor
    ndmpdComm --> ndmpdProp
    ndmpdHandler --> ndmpdConfig
    ndmpdHandler --> ndmpdScsi
    ndmpdHandler --> ndmpdTape
    ndmpdHandler --> ndmpdData
    ndmpdData --> ndmpdUtil
    ndmpdData --> ndmpdMover
    ndmpdData --> tlmLib
    ndmpdMover --> ndmpdUtil
```

- `ndmpd_main.c` 负责加载插件、初始化 door 服务、ZFS 与 TLM 子系统，并启动 `ndmpd_main` 工作线程，过程中直接依赖属性管理与 door 控制接口。【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_main.c†L75-L117】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_main.c†L205-L305】【F:trunk/usr/src/cmd/ndmpd/tlm/tlm_init.c†L492-L540】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_door.c†L64-L147】
- `ndmpd_comm.c` 中的 `ndmpd_main` 打开日志、解析端口并调用 `ndmp_run`，而连接处理器在会话初始化时依次调用数据、文件历史、mover 以及 LBR 初始化逻辑，维护与 door、属性及选择循环的交互。【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_comm.c†L787-L815】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_comm.c†L831-L919】
- `ndmpd_handler.c` 的消息分发表将 NDMP 消息分派到配置、SCSI、磁带、数据等子模块的处理函数，体现了控制面命令处理的依赖关系。【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_handler.c†L117-L560】
- 数据面辅助逻辑位于 `ndmpd_data.c`、`ndmpd_mover.c` 与 `ndmpd_util.c`，前者既操作 mover，又调用 TLM 统计与环境管理接口，对备份模块结构 `ndmp_lbr_params_t` 与 TLM 统计数据进行读写。【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_data.c†L1618-L1767】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_data.c†L1783-L1836】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_mover.c†L1854-L1883】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_util.c†L1045-L1074】【F:trunk/usr/src/cmd/ndmpd/tlm/tlm_proto.h†L62-L153】
- LBR 参数与备份模块通过 `ndmp_lbr_init` 构造，与会话形成双向引用；模块参数结构记录了回调接口，支撑数据/备份流程。【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd.h†L231-L459】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_common.h†L205-L240】【F:trunk/usr/src/cmd/ndmpd/ndmp/ndmpd_util.c†L1045-L1074】

以上图示与说明帮助理解 NDMP 控制面的主要结构体组织与源码模块之间的调用依赖。
